#include "Mesh.h"


void Mesh::draw(Shader& shader) {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::recalcColors() {
    for (int v = 0; v < vertices.size(); v++) {
        float dist = glm::length(vertices[v].position);
        vertices[v].color = colorGradient.getColor(dist);
    }
}

void Mesh::recalcNormals() {
    // http://meshlabstuff.blogspot.com/2009/04/on-computation-of-vertex-normals.html First approach
    // Create shared normals based on areas of triangles
    for (int i = 0; i < indices.size(); i += 6) {
        glm::vec3 uVec(vertices[indices[i + 1]].position - vertices[indices[i]].position);
        glm::vec3 ruVec(vertices[indices[i + 2]].position - vertices[indices[i]].position);
        glm::vec3 rVec(vertices[indices[i + 5]].position - vertices[indices[i]].position);
        
        glm::vec3 t1Norm = glm::cross(ruVec, uVec);
        glm::vec3 t2Norm = glm::cross(rVec, ruVec);

        vertices[indices[i]].normal += t1Norm;
        vertices[indices[i + 1]].normal += t1Norm;
        vertices[indices[i + 2]].normal += t1Norm;

        vertices[indices[i + 3]].normal += t2Norm;
        vertices[indices[i + 4]].normal += t2Norm;
        vertices[indices[i + 5]].normal += t2Norm;
    }
    // Normalize all normals
    for (int v = 0; v < vertices.size(); v++) {
        vertices[v].normal = glm::normalize(vertices[v].normal);
    }
}

void Mesh::initSphere(float radius) {
    float x, y;
    for (int j = 0; j <= res; j++) {
        y = 2 * (float)j / res - 1;
        for (int i = 0; i <= res; i++) {
            x = 2 * (float)i / res - 1;
            vertices.emplace_back(glm::normalize(glm::vec3(x, y, -1.f)) * radius);  // Normalize

            if (i < res && j < res) {
                indices.emplace_back(i + j * (res + 1));
                indices.emplace_back(i + (j + 1) * (res + 1));
                indices.emplace_back(i + 1 + (j + 1) * (res + 1));
                indices.emplace_back(i + j * (res + 1));
                indices.emplace_back(i + 1 + (j + 1) * (res + 1));
                indices.emplace_back(i + 1 + j * (res + 1));
            }
        }
    }
    unsigned int startIndex;                    // starting index for next face
    int vertexSize = (int)vertices.size();      // vertex array size of -Z face
    int indexSize = (int)indices.size();        // index array size of -Z face

    // +Z face by swapping x=>-x, y=>y, z=>-z
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(-vertices[i].position.x, vertices[i].position.y, -vertices[i].position.z));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // +X face by swapping x=>z, y=>y, z=>-x
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(-vertices[i].position.z, vertices[i].position.y, vertices[i].position.x));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // -X face by swapping x=>-z, y=>y, z=>x
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(vertices[i].position.z, vertices[i].position.y, -vertices[i].position.x));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // +Y face by swapping x=>x, y=>-z, z=>y
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(vertices[i].position.x, -vertices[i].position.z, vertices[i].position.y));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // +Y face by swapping x=>x, y=>z, z=>-y
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(vertices[i].position.x, vertices[i].position.z, -vertices[i].position.y));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
}

void Mesh::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glBindVertexArray(0);
}
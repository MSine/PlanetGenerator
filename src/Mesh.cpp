#include "Mesh.h"


// render the mesh
void Mesh::Draw(Shader& shader) {
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Res is the amount of faces on each side of cube before normalization
void Mesh::initSphere(float radius, int res) {
    if (res < 1)
        res = 1;

    float x, y;
    for (int j = 0; j <= res; j++) {
        y = 2 * (float)j / res - 1;
        for (int i = 0; i <= res; i++) {
            x = 2 * (float)i / res - 1;
            vertices.emplace_back(glm::normalize(glm::vec3(x, y, -1.f)) * radius);

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
    // build +X face by swapping x=>z, y=>y, z=>-x
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(-vertices[i].position.z, vertices[i].position.y, vertices[i].position.x));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // build -X face by swapping x=>-z, y=>y, z=>x
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(vertices[i].position.z, vertices[i].position.y, -vertices[i].position.x));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // build +Y face by swapping x=>x, y=>-z, z=>y
    startIndex = vertices.size();
    for (int i = 0; i < vertexSize; i++) {
        vertices.emplace_back(glm::vec3(vertices[i].position.x, -vertices[i].position.z, vertices[i].position.y));
    }
    for (int i = 0; i < indexSize; ++i) {
        indices.push_back(startIndex + indices[i]);
    }
    // build +Y face by swapping x=>x, y=>z, z=>-y
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
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

/*
 * https://learnopengl.com/ uses shaders and buffers
 * https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
 * http://www.opengl-tutorial.org/
 *
 * Maybe adjust all vertexes using vertex shader after creating a sphere
 * */


#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    //glm::vec3 Tangent;
    //glm::vec3 Bitangent;
	//int m_BoneIDs[MAX_BONE_INFLUENCE];
	//float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    //string type;
    //string path;
};



class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        initBuffers();
    }

    //void Draw(Shader &shader)

private:
    unsigned int VBO, EBO;

    // Res is the amount of faces on each side of cube before normalization
    void initSphere(int res) {
        if (res < 1)
            return; //TODO Error
        
        double xPercent, yPercent;
        for (int y = 0; y <= res; y++) {
            yPercent = y / res;
            for (int x = 0; x <= res; x++) {
                xPercent = x / res;
                
            }
        }
    }

    void initBuffers() {
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
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glBindVertexArray(0);
    }
};

#endif
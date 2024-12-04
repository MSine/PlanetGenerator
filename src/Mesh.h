#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

//#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "Shader.hpp"
#include <vector>

/*
 * https://learnopengl.com/ uses shaders and buffers
 * https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
 * http://www.opengl-tutorial.org/
 * */


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;

    Vertex(glm::vec3 pos) : position(pos), normal(0), color(0.9) {}
};


class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;

    Mesh() {}
    void init(float radius, int res) {
        initSphere(radius, res);
        initBuffers();
    }

    void Draw(Shader &shader);

private:
    unsigned int VBO, EBO;

    void initSphere(float radius, int res);
    void initBuffers();
};

#endif
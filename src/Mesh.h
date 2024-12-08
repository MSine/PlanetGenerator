#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

//#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Gradient.hpp"
#include "Shader.hpp"

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
        addStop(1.f, glm::vec3(0.f, 0.f, 1.f));
        addStop(1.1f, glm::vec3(1.f, 1.f, 0.f));
        addStop(1.3f, glm::vec3(0.f, 1.f, 0.f));
        addStop(1.6f, glm::vec3(0.7f, 0.3f, 0.f));
        addStop(1.7f, glm::vec3(1.f, 1.f, 1.f));
        recalcColors();
        initBuffers();
    }

    void addStop(float distance, const glm::vec3& color) {
        colorGradient.addStop(distance, color);
    }

    void recalcColors();

    void Draw(Shader &shader);

private:
    unsigned int VBO, EBO;
    ColorGradient colorGradient;

    void initSphere(float radius, int res);
    void initBuffers();
};

#endif
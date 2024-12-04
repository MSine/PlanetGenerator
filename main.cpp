#include "main.h"
/*
g++ -lglut -lGL -lGLU -lGLEW -o ./build/main main.cpp ./src/Mesh.cpp && ./build/main
*/

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
Shader shader;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

Mesh mesh;

static void render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    mesh.Draw(shader);

    glFlush();
}

static void resizeWindow(int width, int height) {
	SCR_WIDTH = (width == 0) ? 1 : width;
    SCR_HEIGHT = (height == 0) ? 1 : height;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowPosition(100, 100);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("PlanetGenerator");

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    //fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    shader.init("src/shader.vert", "src/shader.frag");
	
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0,0,0,0);
	glutDisplayFunc(render);
	glutReshapeFunc(resizeWindow);

    shader.use();
    mesh.init(2.f, 10);

	glutMainLoop();
    return 0;
}
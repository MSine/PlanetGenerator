#include "main.h"
/*
g++ -lglut -lGL -lGLU -lGLEW -o ./build/main main.cpp ./src/Mesh.cpp && ./build/main
*/

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

// camera
Camera camera;
Shader shader;
glm::vec3 lightPos(0.f, 0.f, -10.f);
glm::vec3 lightColor(1.f, 1.f, 1.f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Mesh planet;

void createPlanet() {
    planet.init(1.f, 100);

    // Add noise layers
    planet.recalcNormals();

    // Add coloring     height, color
        planet.addStop(1.f, glm::vec3(0.f, 0.f, 1.f));
        planet.addStop(1.1f, glm::vec3(1.f, 1.f, 0.f));
        planet.addStop(1.3f, glm::vec3(0.f, 1.f, 0.f));
        planet.addStop(1.6f, glm::vec3(0.7f, 0.3f, 0.f));
        planet.addStop(1.7f, glm::vec3(1.f, 1.f, 1.f));
    planet.recalcColors();

    planet.initBuffers();
}

void render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    // camera/view transformation
    shader.setMat4("view", camera.getViewMatrix());

    shader.setVec3("lightColor", lightColor);
    shader.setVec3("lightPos", lightPos);
    shader.setVec3("viewPos", camera.getPosition());

    planet.draw(shader);

    glFlush();
}

static void resizeWindow(int width, int height) {
	SCR_WIDTH = (width == 0) ? 1 : width;
    SCR_HEIGHT = (height == 0) ? 1 : height;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void mouseDrag(int xposIn, int yposIn) {
    float xpos = (float)(xposIn);
    float ypos = (float)(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if ((button == 3) || (button == 4)) {
        camera.processMouseScroll(button == 3);
    }
    else {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
            firstMouse = true;
        }
    }
    glutPostRedisplay();
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
	
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0,0,0,0);
	glutDisplayFunc(render);
	glutReshapeFunc(resizeWindow);
    glutMotionFunc(mouseDrag);
    glutMouseFunc(mouse);

    shader.use();
    createPlanet();

	glutMainLoop();
    return 0;
}
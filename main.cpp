#include "main.h"


GLuint programID = 0;

static void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    glLoadIdentity();
        glTranslated(0,0,-10);

    glPushMatrix();
        glRotated(60,1,0,0);
        glutSolidSphere(1,20,20);
    glPopMatrix();

    glFlush();
}

static void resizeWindow(int width, int height) {
    float aspectRatio;
	height = (height == 0) ? 1 : height;
	width = (width == 0) ? 1 : width;

	glViewport( 0, 0, width, height );
	aspectRatio = (float)width/(float)height;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 60.0 );

    glMatrixMode( GL_MODELVIEW );
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1600, 900);
	glutCreateWindow("PlanetGenerator");

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    programID = LoadShaders( "src/Shader.vert", "src/Shader.frag" );
	
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0,0,0,0);
	glutDisplayFunc(render);
	glutReshapeFunc(resizeWindow);
	glutMainLoop();
    return 0;
}
#include <iostream>
#include <list>

#include "glut.h"
#include "Mouse.h"
#include "Polygon.h"
#include "MainProgram.h"
#include "Hogdmann.h"

Mouse mouse = Mouse();
MainProgram mainProgram = MainProgram();
bool checked = false;

void handlePassiveMouseMotion(int mouseX, int mouseY)
{
    mouse.SetMousePosition(mouseX, 300 - mouseY);
}

void handleMouseClick(int button, int status, int mouseX, int mouseY) {

    if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN) {
        checked = true;

        if (mouse.modeChoosen == 2)
        {
            if (std::prev(mainProgram.polygons.end())->addPoint(mouse.getXPosition(),mouse.getYPosition()))
            {
                mouse.modeChoosen = 1;
            }
        }

        if (mouse.modeChoosen == 3)
        {
            if (std::prev(mainProgram.windows.end())->addPoint(mouse.getXPosition(),mouse.getYPosition()))
            {
                mouse.modeChoosen = 1;
            }
        }

        if (mouse.modeChoosen == 4) // choose to cut the polygons
        {
            mainProgram.polygonsInWindow = hogdmann(mainProgram.polygons, mainProgram.windows);
            std::cout << mainProgram.polygonsInWindow.size() << std::endl;
        }
    }
    else if (button == GLUT_LEFT_BUTTON && status == GLUT_UP) {
        checked = false;
    }

}

void handleMouseClickedMotion(int mouseX, int mouseY)
{
    checked = true;
}

void display()
{
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Given the coordinates
    gluOrtho2D(0.f, 500.f, 0.f, 300.f);

    //std::cout << "polygons " << mainProgram.polygons.size()  << std::endl;
    //std::cout << "windows " << mainProgram.windows.size() << std::endl;

    if (!mainProgram.polygons.empty())
    {
        mainProgram.drawPolygons(mainProgram.polygons);

        auto polygon = mainProgram.polygons.back();

        if (mouse.modeChoosen == 2 && !polygon.getPoints().empty()) 
        {
            auto lastPoint = polygon.getPoints().back();
            glLineWidth(polygon._width);
            glBegin(GL_LINES);
            glColor3f(polygon.r, polygon.g, polygon.b);
            glVertex2f(lastPoint._x, lastPoint._y);
            glVertex2f(mouse.getXPosition(), mouse.getYPosition());
            glEnd();
        }
    }

    if (!mainProgram.windows.empty())
    {
        mainProgram.drawPolygons(mainProgram.windows);

        auto window = mainProgram.windows.back();

        if (mouse.modeChoosen == 3 && !window.getPoints().empty()) 
        {
            auto lastPoint = window.getPoints().back();
            glLineWidth(window._width);
            glBegin(GL_LINES);
            glColor3f(window.r, window.g, window.b);
            glVertex2f(lastPoint._x, lastPoint._y);
            glVertex2f(mouse.getXPosition(), mouse.getYPosition());
            glEnd();
        }
    }
    
    if (!mainProgram.polygonsInWindow.empty())
    {
        mainProgram.drawPolygons(mainProgram.polygonsInWindow);
    }

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void processMenuEvents(int option) 
{
    mouse.modeChoosen = option;

    if (mouse.modeChoosen == 2) // choose to draw a new polygon
    {
        mainProgram.polygons.push_back(Polygon(1, 0, 0));
    }

    if (mouse.modeChoosen == 3) // choose to draw a new window
    {
        mainProgram.windows.push_back(Polygon(0, 1, 0));
    }
};

void createGLUTMenus() 
{
    const auto menu = glutCreateMenu(processMenuEvents);

    glutAddMenuEntry("polygone", 2);
    glutAddMenuEntry("tracé fenêtre", 3);
    glutAddMenuEntry("fenêtrage", 4);
    glutAddMenuEntry("remplissage", 5);
    glutAddMenuEntry("couleurs", 6);

    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    mainProgram.init();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // init size / position of the window
    glutInitWindowSize(500, 300);
    glutInitWindowPosition(0, 0);

    // init window
    glutCreateWindow("paintLike");

    //init right click menu
    createGLUTMenus();

    // init eventhandlers
    glutPassiveMotionFunc(handlePassiveMouseMotion);
    glutMouseFunc(handleMouseClick);
    glutMotionFunc(handleMouseClickedMotion);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
#include "Mouse.h"

void Mouse::Polygon() {}

void Mouse::createWindow() {}

void Mouse::windows() {}

//! a déplacer dans polygon

void Mouse::fillingInit() { 
    PixelColor currentColor;
    PixelColor newColor;
    newColor.r = 0.f;
    newColor.g = 0.f;
    newColor.b = 0.f;
    glReadPixels(xPosition, yPosition, 1, 1, GL_RGB, GL_FLOAT, &currentColor);
    
    filling(xPosition, yPosition, currentColor, newColor);
}

void Mouse::filling(const int x, const int y, const PixelColor oldColor, const PixelColor newColor) const {
    PixelColor currentColor;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &currentColor);
    std::cout << "x : " << x << " y : " << y << std::endl;
    if (currentColor == oldColor) {
        glBegin(GL_POINTS);
            glColor3f(newColor.r, newColor.b, newColor.g);
            glVertex2i(xPosition, yPosition);
        glEnd();
        glFlush();
        filling(x + 1, y, oldColor, newColor);
        filling(x, y + 1, oldColor, newColor);
        filling(x - 1, y, oldColor, newColor);
        filling(x, y - 1, oldColor, newColor);
    }
    return;
}

void Mouse::selectColor() {

}

void Mouse::SetMousePosition(const int xMouse, const int yMouse) {
    xPosition = xMouse;
    yPosition = yMouse;
}

GLuint Mouse::getXPosition() {
    return xPosition;
}

GLuint Mouse::getYPosition() {
    return yPosition;
}

bool Mouse::applyMode() {
    switch (modeChoosen) {
        case 1:
            // default mode
            break;
        case 2:
            //Polygon();
            return true;
        case 3:
            //createWindow();
            break;
        case 4:
            //windows();
            break;
        case 5:
            //fillingInit();
            return false;
        case 6:
            //selectColor();
            break;
    }
    return false;
}
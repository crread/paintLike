#ifndef MOUSE_HEADER_WINDOW
#define MOUSE_HEADER_WINDOW

#include <iostream>

#include "glut.h"

struct PixelColor {
	GLfloat r;
	GLfloat g;
	GLfloat b;

	bool operator== (const PixelColor& pixelColor) {
		return (r == pixelColor.r && g == pixelColor.g && b == pixelColor.b);
	}
};

class Mouse {

	GLuint xPosition;
	GLuint yPosition;

	void Polygon();
	void createWindow();
	void windows();
	void fillingInit();
	void filling(const int x, const int y, const PixelColor oldColor,const PixelColor newColor) const;
	void selectColor();

public:
	GLint modeChoosen;
	GLfloat r, g, b;

	Mouse() {
		modeChoosen = 1;
		r = g = b = xPosition = yPosition = 0;
	};

	void SetMousePosition(const int xMouse, const int yMouse);

	GLuint getXPosition();
	GLuint getYPosition();

	bool applyMode();
};

#endif // !MOUSE_HEADER_WINDOW
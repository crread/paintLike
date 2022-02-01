#ifndef POLYGON_HEADER_WINDOW
#define POLYGON_HEADER_WINDOW

#include <iostream>
#include <cmath>
#include <list>
#include <vector>

#include "glut.h"

struct Point
{
	int _x;
	int _y;
	int _id;

	Point(const int x, const int y) : _x(x), _y(y) {};
	Point(const int x, const int y, const int id) : _x(x), _y(y), _id(id) {};
};

class Polygon {

	std::vector<Point> points;

	int getOrientation() const;
	std::vector<Point> getNormals() const;
	bool nearPointFromSamePolygon(Point* point);

public:

	float r, g, b = 0;
	float _width;
	GLenum mode = GL_LINES;

	Polygon(float width) : _width(width) {};
	Polygon(float _r, float _g, float _b) : r(_r), g(_g), b(_b), _width(1) {};
	std::vector<Point> getPoints() const;
	bool pointIsEmpty() const;
	bool addPoint(int x, int y);
	bool cyrusBeck(std::vector<Polygon> polygons);
};

#endif
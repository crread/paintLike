#ifndef POLYGON_HEADER_WINDOW
#define POLYGON_HEADER_WINDOW

#include <iostream>
#include <cmath>
#include <list>
#include <vector>

#include "glut.h"

#define INF 10000 // use to extend a point and check if it's inside a polygon

struct Point
{
	int _x;
	int _y;
	int _id;

	Point(int x, int y, int id) : _x(x), _y(y), _id(id) {};
};

class Polygon {

	std::vector<Point> points;

	bool onSegment(Point p, Point q, Point r);
	int orientation(Point p, Point q, Point r);
	bool doIntersect(Point p1, Point q1, Point p2, Point q2);
	bool pointIsInsidePolygon(const Point point);
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
#include <iostream>

#include "Polygon.h"

bool Polygon::addPoint(int x, int y) {

	auto point = Point(x, y, points.size());

	auto getClosed = nearPointFromSamePolygon(&point);
	points.push_back(point);

	return getClosed;
}

std::vector<Point> Polygon::getPoints() const 
{
	return points;
}

bool Polygon::pointIsEmpty() const 
{
	return points.empty();
}

bool Polygon::onSegment(Point p, Point q, Point r)
{
	if (q._x <= std::max(p._x, r._x) && q._x >= std::min(p._x, r._x) &&
		q._y <= std::max(p._y, r._y) && q._y >= std::min(p._y, r._y))
		return true;
	return false;
}

int Polygon::orientation(Point p, Point q, Point r)
{
	int val = (q._y - p._y) * (r._x - q._x) - (q._x - p._x) * (r._y - q._y);

	if (val == 0) return 0; // collinear 
	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

bool Polygon::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return true;

	if (o1 == 0 && onSegment(p1, p2, q1)) return true;
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false;
}

bool Polygon::pointIsInsidePolygon(const Point point) 
{
	Point extreme = Point(INF, point._y, 0);

	int i = 0;
	int count = 0;

	do
	{
		int next = (i + 1) % points.size();
		if (doIntersect(points.at(i), points.at(next), point, extreme))
		{
			if (orientation(points.at(i), point, points.at(next)) == 0)
			{
				std::cout << " ? ? ? ? " << std::endl;
				return onSegment(points.at(i), point, points.at(next));
			}

			count++;
			std::cout << "counter : " << count << " size : " << points.size()  << std::endl;
		}
	} while (i != 0);

	return count&1; // return true if odd
}

bool Polygon::cyrusBeck(std::vector<Polygon> polygons) 
{
	for (auto p = polygons.begin(); p != polygons.end(); ++p)
	{
		int counter = 0;
		auto points = p->getPoints();

		std::cout << "size : " << points.size() << std::endl;
		for (auto point = points.begin(); point != points.end(); ++point)
		{
			if (pointIsInsidePolygon(*point))
			{
				counter++;
			}
		}
		std::cout << counter << std::endl;
	}
	return true;
}

bool Polygon::nearPointFromSamePolygon(Point* point)
{
	if (!points.empty())
	{
		GLushort maxSize = 5;
		for (auto p = points.begin(); p != points.end(); ++p)
		{
			if (std::abs(p->_x - point->_x) < maxSize && std::abs(p->_y - point->_y) < maxSize)
			{
				point->_x = p->_x;
				point->_y = p->_y;
				return true;
			}
		}
	}

	return false;
}
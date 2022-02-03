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

int Polygon::getOrientation() const 
{
	auto pointsSize = points.size();
	int orientation = 0;
	int i = 0;	

	if (pointsSize >= 3) {
		do
		{

			if (i >= pointsSize)
			{
				return 0;
			}

			orientation = (points.at((i + 1) % pointsSize)._x * points.at((i + 2) % pointsSize)._y + points.at(i)._x * points.at((i + 2) % pointsSize)._y + points.at((i + 2) % pointsSize)._x * points.at(i)._y) - (points.at((i + 1) % pointsSize)._x * points.at(i)._y + points.at((i + 2) % pointsSize)._x * points.at((i + 1) % pointsSize)._y + points.at(i)._x * points.at((i + 2) % pointsSize)._y);

			i++;

		} while (orientation == 0);

		// orientation < 0 => clockwise orientation
		// orientation > 0 => counterclockwise orientation

		return orientation < 0 ? -1 : 1;
	}

	return 0;
}

std::vector<Point> Polygon::getNormals() const
{
	auto pointsSize = points.size();
	int orientation = this->getOrientation();
	std::cout << orientation << std::endl;
	std::vector<Point> normals;

	//if (orientation != 0) {

	//	for (int i = 0; i < pointsSize; i++)
	//	{
	//		if (orientation == -1) 
	//		{
	//			normals.push_back(Point(
	//				points.at(pointsSize % i + 1)._y - points.at(i)._y,
	//				-1 * (points.at(pointsSize % i + 1)._x - points.at(i)._x)
	//			));
	//		}
	//		else 
	//		{
	//			normals.push_back(Point(
	//				-1 * (points.at(pointsSize % i + 1)._y - points.at(i)._y),
	//				points.at(pointsSize % i + 1)._x - points.at(i)._x
	//			));
	//		}
	//	}
	//}

	return normals;
}

bool Polygon::cyrusBeck()
//bool Polygon::cyrusBeck(std::vector<Polygon> polygons) 
{
	std::vector<Point> normals = this->getNormals();
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
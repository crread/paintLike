#pragma once
#include "Polygon.h"
#include <algorithm>
#include <iostream>

std::vector<Polygon> hogdmann(std::vector<Polygon> polygons, std::vector<Polygon> windows);

bool onSegment(Point p, Point q, Point r);

int orientation(Point p, Point q, Point r);

bool isInside(const std::vector<Point> window, Point p);

bool segmentIntersection(const Point& A, const Point& B, const Point& C, const Point& D, Point& result);

Point getIntersectionPoint(const Polygon& window, const Point& pointA, const Point& pointB);

bool CollisionDroiteSeg(Point A, Point B, Point O, Point P);

bool CollisionSegSeg(Point A, Point B, Point O, Point P);
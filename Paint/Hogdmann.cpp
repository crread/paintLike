#include "Hogdmann.h"

std::vector<Polygon> hogdmann(std::vector<Polygon> polygons, std::vector<Polygon> windows)
{
	std::vector<Polygon> resultList;

	for (auto const& window : windows)
	{
		for (auto const& polygon : polygons)
		{
			auto points = polygon.getPoints();
			
			if (!points.empty() && points.size() > 1)
			{
				Polygon newPoly(0, 0, 1);

				std::vector<Point> windowPoints = window.getPoints();

				Point pointA = points.front();
				bool pointAInside = isInside(windowPoints, pointA);

				for (auto const& pointB : points)
				{

					if ((pointB._x != pointA._x) || (pointB._y != pointA._y))
					{
						bool pointBInside = isInside(windowPoints, pointB);

						if(pointAInside == false && pointBInside == true)
						{
							Point result = getIntersectionPoint(window, pointA, pointB);
							newPoly.addPoint(result._x, result._y);
						}

						//Si le point B est à l'intérieur on l'ajoute toujours
						if (pointBInside == true)
						{
							newPoly.addPoint(pointB._x, pointB._y);
							std::cout << "inside" << pointB._x << " " << pointB._y << std::endl;

						}

						if(pointBInside == false && pointAInside == true)
						{
							Point result = getIntersectionPoint(window, pointA, pointB);
							newPoly.addPoint(result._x, result._y);
						}

						pointAInside = pointBInside;
					}
					pointA = pointB;
					
				}

				if (newPoly.getPoints().size() > 2) {
					Point front = newPoly.getPoints().front();

					newPoly.addPoint(front._x, front._y);

					resultList.push_back(newPoly);
				}
			}
		}
	}

	return resultList;
}

Point getIntersectionPoint(const Polygon &window, const Point& pointA, const Point& pointB)
{
	Point result = { 0, 0, 0 };

	Point pointC = window.getPoints().back();
	std::vector<Point> windowPoints = window.getPoints();
	std::vector<Point>::iterator pointD = windowPoints.begin();

	while (!segmentIntersection(pointA, pointB, pointC, *pointD, result)) {

		pointC = *pointD;
		pointD++;
	}

	return result;
}

bool onSegment(Point p, Point q, Point r)
{
	if (q._x <= std::max(p._x, r._x) && q._x >= std::min(p._x, r._x) &&
		q._y <= std::max(p._y, r._y) && q._y >= std::min(p._y, r._y))
		return true;
	return false;
}

// 0 --> p, q et r sont colinéaire
// 1 --> sens horaire
// 2 --> sens anti-horaire
int orientation(Point a, Point b, Point c)
{
	float AB_x = a._x - b._x;
	float AB_y = a._y - b._y;

	float AC_x = a._x - c._x;
	float AC_y = a._y - c._y;

	int val = AC_x * AB_y - AC_y * AB_x;

	if (val == 0) return 0; // collinéaire 
	return (val > 0) ? 1 : 2; // sens horaire ou sens anti-hoaraire
}

//Retourne vrai si le point est à l'intérieur
bool isInside(const std::vector<Point> window, Point p)
{
	// Il doit y avoir au moins trois vertex
	if (window.size() < 3) return false;

	Point extreme = {1000000000, p._y, 0};

	//Compte les intersections 
	int count = 0, i = 0;
	
	Point pointA = window.back();

	int previousOrientation = 0;
	bool init = true;

	for(auto const& pointB : window)
	{
		if ((pointB._x != pointA._x) || (pointB._y != pointA._y))
		{
			int currentOrientation = orientation(pointA, pointB, p);

			//std::cout << currentOrientation << std::endl;

			if (init == true)
			{
				init = false;
				previousOrientation = currentOrientation;

				//Vérifie s'il sont colinéaire puis vérifie si le point est sur le segment
				if (currentOrientation == 0)
				{
					return onSegment(pointA, p, pointB);
				}
			}
			else {

				//Vérfie si la ligne intersecte une ligne de la fenêtre
				if (previousOrientation != currentOrientation)
				{
					//Vérifie s'il sont colinéaire puis vérifie si le point est sur le segment
					if (currentOrientation == 0)
					{
						return onSegment(pointA, p, pointB);
					}

					return false;
				}
			}
		}
		
		pointA = pointB;
	}

	return true;

	// Retourne vrai si le compte est impair
	std::cout << count << std::endl;
	return count & 1;
}

bool segmentIntersection(const Point& A, const Point& B, const Point& I, const Point& P, Point& result)
{
	Point AB{(A._x - B._x), (A._y - B._y), 0};
	Point IP{(I._x - P._x), (I._y - P._y), 0 };

	float det = AB._x * IP._y - AB._y * IP._x;

	if(det == 0)
	{
		//Parallèle ou colinéaire
		return false;
	}else {

		if (CollisionSegSeg(A, B, I, P)) {
			float t1 = ((A._x * B._y - A._y * B._x) * (I._x - P._x) - (A._x - B._x) * (I._x * P._y - I._y * P._x)) / det;
			float t2 = ((A._x * B._y - A._y * B._x) * (I._y - P._y) - (A._y - B._y) * (I._x * P._y - I._y * P._x)) / det;

			result._x = t1;
			result._y = t2;

			std::cout << "true" << std::endl;

			return true;
		}

		return false;
	}
}

bool CollisionDroiteSeg(Point A, Point B, Point O, Point P)
{
	Point AO{ 0, 0, 0 }, AP{ 0, 0, 0 }, AB{ 0, 0, 0 };
	AB._x = B._x - A._x;
	AB._y = B._y - A._y;
	AP._x = P._x - A._x;
	AP._y = P._y - A._y;
	AO._x = O._x - A._x;
	AO._y = O._y - A._y;
	if ((AB._x * AP._y - AB._y * AP._x) * (AB._x * AO._y - AB._y * AO._x) < 0)
		return true;
	else
		return false;
}

bool CollisionSegSeg(Point A, Point B, Point O, Point P)
{
	if (CollisionDroiteSeg(A, B, O, P) == false)
		return false;  // inutile d'aller plus loin si le segment [OP] ne touche pas la droite (AB)
	if (CollisionDroiteSeg(O, P, A, B) == false)
		return false;
	return true;
}
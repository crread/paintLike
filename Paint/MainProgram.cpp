#include <iostream>

#include "MainProgram.h"

void MainProgram::init() const {}

void MainProgram::drawPolygons(std::vector<Polygon> polygons) const {

    if (!polygons.empty())
    {

        for (auto const& polygon : polygons)
        {
            auto points = polygon.getPoints();

            if (!points.empty() && points.size() > 1)
            {
                glBegin(GL_LINES);
                glColor3f(polygon.r, polygon.g, polygon.b);

                for (auto p = points.begin(); p != std::prev(points.end()); ++p)
                {
                    glLineWidth(polygon._width);
                    glVertex3f(p->_x, p->_y, 0.f);
                    glVertex3f(std::next(p)->_x, std::next(p)->_y, 0.f);   
                }

                glEnd();
            }
        }

    }
}
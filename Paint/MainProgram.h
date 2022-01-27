#ifndef MAINPROGRAM_HEADER_WINDOW
#define MAINPROGRAM_HEADER_WINDOW

#include <list>

#include "Polygon.h"

class MainProgram
{
public:

    std::vector<Polygon> polygons;
    std::vector<Polygon> windows;
    std::vector<Polygon> polygonsInWindow;

    MainProgram() {};

    void drawPolygons(std::vector<Polygon> polygons) const;
    void init() const;
};

#endif // !MAINPROGRAM_HEADER_WINDOW
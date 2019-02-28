#pragma once
#include <SDL.h>
#include <vector>
#include "Graphics.h"
using namespace std;

extern const int WIDTH;
extern const int HEIGHT;
extern const double PI;

class Mesh
{
public:
	Mesh(SDL_Surface* screen);
	void draw();
	void event();
private:
	struct Point
	{
		Point(double x = 0, double y = 0, double z = 0) : x{ x }, y{ y }, z{ z } {}
		double x, y, z;
	};
	struct Edge
	{
		Edge(Point point1 = { }, Point point2 = { }) : point1{ point1 }, point2{ point2 } {}
		Point point1, point2;
	};
	void rotateVerticesAroundX(double angle);
	void rotateVerticesAroundY(double angle);
	void rotateVerticesAroundZ(double angle);
	void createCubeEdges(); // Сreating cube edges using vertices
	void drawWireFrame(Uint8 red, Uint8 green, Uint8 blue);
	void downFaces();
	void upFaces();
	void rotatePointAroundX(Point& point1, const Point& point2, double angle);
	void rotatePointAroundY(Point& point1, const Point& point2, double angle);
	void rotatePointAroundZ(Point& point1, const Point& point2, double angle);
	SDL_Surface *screen;
	int i, i1, ev;
	vector<Edge> edges;
	vector<Point> vertices, verticesCopy;
};

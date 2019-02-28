#include "Mesh.h"

Mesh::Mesh(SDL_Surface* screen) : screen{ screen }, i{ 0 }, i1{ 0 }, ev{ 0 }, edges(19), vertices(14), verticesCopy(14)
{
	double R = 100;
	vertices[0] = Point(-R, -R, R); //0
	vertices[1] = Point(-R, -R, -R); // 1
	vertices[2] = Point(-R, -R, -R); // 2
	vertices[3] = Point(R, -R, -R); // 3
	vertices[4] = Point(R, -R, -R); // 4
	vertices[5] = Point(-R, -R, -R); // 5
	vertices[6] = Point(-R, -R, R); // 6
	vertices[7] = Point(R, -R, R); // 7
	vertices[8] = Point(R, -R, R); // 8
	vertices[9] = Point(-R, -R, R); // 9
	vertices[10] = Point(-R, R, R); // 10
	vertices[11] = Point(-R, R, -R); // 11
	vertices[12] = Point(R, R, -R); // 12
	vertices[13] = Point(R, R, R); // 13
}

void Mesh::draw()
{
	if (ev == 1)
	{
		downFaces();
	}
	else if (ev == 3)
	{
		upFaces();
	}
	verticesCopy = vertices;
	rotateVerticesAroundY(i / 10.0);
	createCubeEdges();
	drawWireFrame(0, 255, 0);
	if (++i == 3600)
	{
		i = 0;
	}
}

void Mesh::event()
{
	if (++ev == 4)
	{
		ev = 0;
	}
}

void Mesh::rotatePointAroundX(Point& point, const Point& basePoint, double angle)
{
	// rotation of a point (point) around the base point (basePoint) along the axis X
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	point.y -= basePoint.y;
	point.z -= basePoint.z;
	double temp = point.y * cos_ - point.z * sin_;
	point.z = point.y * sin_ + point.z * cos_ + basePoint.z;
	point.y = temp + basePoint.y;
}

void Mesh::rotatePointAroundY(Point& point, const Point& basePoint, double angle)
{
	// rotation of a point (point) around the base point (basePoint) along the axis Y
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	point.x -= basePoint.x;
	point.z -= basePoint.z;
	double temp = point.x * cos_ - point.z * sin_;
	point.z = point.x * sin_ + point.z * cos_ + basePoint.z;
	point.x = temp + basePoint.x;
}

void Mesh::rotatePointAroundZ(Point& point, const Point& basePoint, double angle)
{
	// rotation of a point (point) around the base point (basePoint) along the axis Z
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	point.x -= basePoint.x;
	point.y -= basePoint.y;
	double temp = point.x * cos_ - point.y * sin_;
	point.y = point.x * sin_ + point.y * cos_ + basePoint.y;
	point.x = temp + basePoint.x;
}

void Mesh::downFaces()
{
	double angle = 0.050;
	if (i1 <= 1800)
	{
		rotatePointAroundZ(vertices[0], vertices[10], -angle);
		rotatePointAroundZ(vertices[1], vertices[11], -angle);
		rotatePointAroundZ(vertices[5], vertices[4], angle);
		rotatePointAroundZ(vertices[6], vertices[7], angle);
		rotatePointAroundX(vertices[2], vertices[11], angle);
		rotatePointAroundX(vertices[3], vertices[12], angle);
		rotatePointAroundX(vertices[9], vertices[10], -angle);
		rotatePointAroundX(vertices[8], vertices[13], -angle);
		rotatePointAroundZ(vertices[5], vertices[12], angle);
		rotatePointAroundZ(vertices[6], vertices[13], angle);
		rotatePointAroundZ(vertices[4], vertices[12], angle);
		rotatePointAroundZ(vertices[7], vertices[13], angle);
		i1++;
	}
}

void Mesh::upFaces()
{
	double angle = 0.050;
	if (i1 >= 0)
	{
		rotatePointAroundZ(vertices[0], vertices[10], angle);
		rotatePointAroundZ(vertices[1], vertices[11], angle);
		rotatePointAroundZ(vertices[5], vertices[4], -angle);
		rotatePointAroundZ(vertices[6], vertices[7], -angle);
		rotatePointAroundX(vertices[2], vertices[11], -angle);
		rotatePointAroundX(vertices[3], vertices[12], -angle);
		rotatePointAroundX(vertices[9], vertices[10], angle);
		rotatePointAroundX(vertices[8], vertices[13], angle);
		rotatePointAroundZ(vertices[5], vertices[12], -angle);
		rotatePointAroundZ(vertices[6], vertices[13], -angle);
		rotatePointAroundZ(vertices[4], vertices[12], -angle);
		rotatePointAroundZ(vertices[7], vertices[13], -angle);
		i1--;
	}
}

void Mesh::drawWireFrame(Uint8 red, Uint8 green, Uint8 blue)
{
	double distance = 900;
	for (int i = 0; i < edges.size(); ++i)
	{
		int x1 = distance * edges[i].point1.x / (distance - edges[i].point1.z) + WIDTH / 2;
		int y1 = distance * edges[i].point1.y / (distance - edges[i].point1.z) + HEIGHT / 2;
		int x2 = distance * edges[i].point2.x / (distance - edges[i].point2.z) + WIDTH / 2;
		int y2 = distance * edges[i].point2.y / (distance - edges[i].point2.z) + HEIGHT / 2;
		drawLine(screen, x1, y1, x2, y2, red, green, blue);
	}
}

void Mesh::createCubeEdges()
{
	edges[0] = Edge(verticesCopy[0], verticesCopy[1]);
	edges[1] = Edge(verticesCopy[1], verticesCopy[11]);
	edges[2] = Edge(verticesCopy[11], verticesCopy[2]);
	edges[3] = Edge(verticesCopy[2], verticesCopy[3]);
	edges[4] = Edge(verticesCopy[3], verticesCopy[12]);
	edges[5] = Edge(verticesCopy[12], verticesCopy[4]);
	edges[6] = Edge(verticesCopy[4], verticesCopy[5]);
	edges[7] = Edge(verticesCopy[5], verticesCopy[6]);
	edges[8] = Edge(verticesCopy[6], verticesCopy[7]);
	edges[9] = Edge(verticesCopy[4], verticesCopy[7]);
	edges[10] = Edge(verticesCopy[7], verticesCopy[13]);
	edges[11] = Edge(verticesCopy[13], verticesCopy[8]);
	edges[12] = Edge(verticesCopy[8], verticesCopy[9]);
	edges[13] = Edge(verticesCopy[9], verticesCopy[10]);
	edges[14] = Edge(verticesCopy[10], verticesCopy[0]);
	edges[15] = Edge(verticesCopy[10], verticesCopy[11]);
	edges[16] = Edge(verticesCopy[11], verticesCopy[12]);
	edges[17] = Edge(verticesCopy[12], verticesCopy[13]);
	edges[18] = Edge(verticesCopy[13], verticesCopy[10]);
}

void Mesh::rotateVerticesAroundX(double angle)
{
	// Rotation of vertices around the axis X
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		double temp = vertices[i].y * cos_ - vertices[i].z * sin_;
		vertices[i].z = vertices[i].y * sin_ + vertices[i].z * cos_;
		vertices[i].y = temp;
	}
}

void Mesh::rotateVerticesAroundY(double angle)
{
	// Rotation of vertices around the axis Y
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	for (size_t i = 0; i < verticesCopy.size(); ++i)
	{
		double temp = verticesCopy[i].x * cos_ - verticesCopy[i].z * sin_;
		verticesCopy[i].z = verticesCopy[i].x * sin_ + verticesCopy[i].z * cos_;
		verticesCopy[i].x = temp;
	}
}

void Mesh::rotateVerticesAroundZ(double angle)
{
	// Rotation of vertices around the axis Z
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		double temp = vertices[i].x * cos_ - vertices[i].y * sin_;
		vertices[i].y = vertices[i].x * sin_ + vertices[i].y * cos_;
		vertices[i].x = temp;
	}
}

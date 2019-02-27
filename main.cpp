#include <iostream>
#include <SDL.h> // using SDL 1.2.15
#include <vector>
using namespace std;

constexpr int WIDTH = 1800;
constexpr int HEIGHT = 900;
constexpr int BPP = 4;
constexpr int DEPTH = 32;
constexpr double PI = 3.1415926535897932384626433832795f;

struct Point
{
	Point(double x, double y, double z) : x{ x }, y{ y }, z{ z } {}
	double x, y, z;
};

struct Edge
{
	Edge(Point point1, Point point2) : point1{ point1 }, point2{ point2 } {}
	Point point1, point2;
};


void clearScreen(SDL_Surface* screen);
inline void drawPixel(SDL_Surface *screen, int x, int y, Uint8 red, Uint8 green, Uint8 blue);
void drawLine(SDL_Surface* screen, int x1, int y1, int x2, int y2, Uint8 red, Uint8 green, Uint8 blue);
void drawCircle(SDL_Surface* screen, int x0, int y0, int radius, Uint8 red, Uint8 green, Uint8 blue);

void rotateVerticesAroundX(vector<Point>& vertices, double angle);
void rotateVerticesAroundY(vector<Point>& vertices, double angle);
void rotateVerticesAroundZ(vector<Point>& vertices, double angle);
void createCubeVertices(vector<Point>& vertices); // Сreating cube vertices
vector<Edge> createCubeEdges(const vector<Point>& vertexes); // Сreating cube edges using vertices
void drawWireFrame(SDL_Surface* screen, const vector<Edge>& edges, Uint8 red, Uint8 green, Uint8 blue);
void downFaces1(vector<Point>& vertices);
void downFaces2(vector<Point>& vertices);
void rotatePointAroundX(Point& point1, const Point& point2, double angle);
void rotatePointAroundY(Point& point1, const Point& point2, double angle);
void rotatePointAroundZ(Point& point1, const Point& point2, double angle);

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
	SDL_Event event;
	SDL_Surface *screen;
	int keypress{}, i{}, i1{};
	vector<Edge> cube;
	vector<Point> vertices;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)))
	{
		SDL_Quit();
		return 1;
	}
	createCubeVertices(vertices);
	while (!keypress)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				keypress = 1;
				break;
			case SDL_KEYDOWN:
				keypress = 1;
				break;
			}
		}
		clearScreen(screen);
		if (i1 <= 900)
		{
			downFaces1(vertices);
			++i1;
		}
		if(i1>900 && i1 < 1800)
		{
			downFaces2(vertices);
			++i1;
		}
		vector<Point> verticesCopy(vertices);
		rotateVerticesAroundY(verticesCopy, i / 10.0);
		drawWireFrame(screen, createCubeEdges(verticesCopy), 0, 255, 0);
		SDL_Flip(screen);
		i++;
		if (i == 3600)
		{
			i = 0;
		}
		
	}
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}

void rotatePointAroundX(Point& point, const Point& basePoint, double angle)
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
void rotatePointAroundY(Point& point, const Point& basePoint, double angle)
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

void rotatePointAroundZ(Point& point, const Point& basePoint, double angle)
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

void downFaces1(vector<Point>& vertexes)
{
	double angle = 0.1;
	rotatePointAroundZ(vertexes[0], vertexes[10], -angle);
	rotatePointAroundZ(vertexes[1], vertexes[11], -angle);
	rotatePointAroundZ(vertexes[5], vertexes[4], angle);
	rotatePointAroundZ(vertexes[6], vertexes[7], angle);
	rotatePointAroundX(vertexes[2], vertexes[11], angle);
	rotatePointAroundX(vertexes[3], vertexes[12], angle);
	rotatePointAroundX(vertexes[9], vertexes[10], -angle);
	rotatePointAroundX(vertexes[8], vertexes[13], -angle);
}
void downFaces2(vector<Point>& vertexes)
{
	double angle = 0.1;
	rotatePointAroundZ(vertexes[5], vertexes[12], angle);
	rotatePointAroundZ(vertexes[6], vertexes[13], angle);
	rotatePointAroundZ(vertexes[4], vertexes[12], angle);
	rotatePointAroundZ(vertexes[7], vertexes[13], angle);
}

void drawWireFrame(SDL_Surface* screen, const vector<Edge>& edges, Uint8 red, Uint8 green, Uint8 blue)
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

void createCubeVertices(vector<Point>& vertexes)
{
	double R = 100;
	vertexes.push_back({ -R, -R, R }); //0
	vertexes.push_back({ -R, -R, -R }); // 1
	vertexes.push_back({ -R, -R, -R }); // 2
	vertexes.push_back({ R, -R, -R }); // 3
	vertexes.push_back({ R, -R, -R }); // 4
	vertexes.push_back({ -R, -R, -R }); // 5
	vertexes.push_back({ -R, -R, R }); // 6
	vertexes.push_back({ R, -R, R }); // 7
	vertexes.push_back({ R, -R, R }); // 8
	vertexes.push_back({ -R, -R, R }); // 9
	vertexes.push_back({ -R, R, R }); // 10
	vertexes.push_back({ -R, R, -R }); // 11
	vertexes.push_back({ R, R, -R }); // 12
	vertexes.push_back({ R, R, R }); // 13
	vertexes.shrink_to_fit();
}

vector<Edge> createCubeEdges(const vector<Point>& vertexes)
{
	vector<Edge> cube;
	cube.push_back({ vertexes[0], vertexes[1] });
	cube.push_back({ vertexes[1], vertexes[11] });
	cube.push_back({ vertexes[11], vertexes[2] });
	cube.push_back({ vertexes[2], vertexes[3] });
	cube.push_back({ vertexes[3], vertexes[12] });
	cube.push_back({ vertexes[12], vertexes[4] });
	cube.push_back({ vertexes[4], vertexes[5] });
	cube.push_back({ vertexes[5], vertexes[6] });
	cube.push_back({ vertexes[6], vertexes[7] });
	cube.push_back({ vertexes[4], vertexes[7] });
	cube.push_back({ vertexes[7], vertexes[13] });
	cube.push_back({ vertexes[13], vertexes[8] });
	cube.push_back({ vertexes[8], vertexes[9] });
	cube.push_back({ vertexes[9], vertexes[10] });
	cube.push_back({ vertexes[10], vertexes[0] });
	cube.push_back({ vertexes[10], vertexes[11] });
	cube.push_back({ vertexes[11], vertexes[12] });
	cube.push_back({ vertexes[12], vertexes[13] });
	cube.push_back({ vertexes[13], vertexes[10] });
	cube.shrink_to_fit(); 
	return cube; // return vector of edges
}


void clearScreen(SDL_Surface *screen)
{
	SDL_Rect d = { 0,0, WIDTH, HEIGHT };
	SDL_FillRect(screen, &d, 75);
}

inline void drawPixel(SDL_Surface *screen, int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		Uint32 *pixmem32;
		Uint32 colour;
		int ytimesw = y * screen->pitch / BPP;
		colour = SDL_MapRGB(screen->format, red, green, blue);
		pixmem32 = (Uint32*)screen->pixels + ytimesw + x;
		*pixmem32 = colour;
	}
}


void drawLine(SDL_Surface* screen, int x1, int y1, int x2, int y2, Uint8 red, Uint8 green, Uint8 blue)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	drawPixel(screen, x2, y2, red, green, blue);
	while (x1 != x2 || y1 != y2)
	{
		drawPixel(screen, x1, y1, red, green, blue);
		const int error2 = error << 1;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void drawCircle(SDL_Surface* screen, int x0, int y0, int radius, Uint8 red, Uint8 green, Uint8 blue)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		drawPixel(screen, x0 + x, y0 + y, red, green, blue);
		drawPixel(screen, x0 + x, y0 - y, red, green, blue);
		drawPixel(screen, x0 - x, y0 + y, red, green, blue);
		drawPixel(screen, x0 - x, y0 - y, red, green, blue);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

void rotateVerticesAroundX(vector<Point>& vertices, double angle)
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

void rotateVerticesAroundY(vector<Point>& vertices, double angle)
{
	// Rotation of vertices around the axis Y
	angle = angle * PI / 180;
	double cos_ = cos(angle);
	double sin_ = sin(angle);
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		double temp = vertices[i].x * cos_ - vertices[i].z * sin_;
		vertices[i].z = vertices[i].x * sin_ + vertices[i].z * cos_;
		vertices[i].x = temp;
	}
}

void rotateVerticesAroundZ(vector<Point>& vertices, double angle)
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

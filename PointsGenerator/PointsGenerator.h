#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <math.h>

#define PI 3.141592653589
#define _USE_MATH_DEFINES

struct Coord {
	double x;
	double y;
	double z;
};

typedef std::vector<Coord> curve;
typedef std::vector<curve> Surface;

class PointsGenerator {
public:
	PointsGenerator(char** argv){
		programName = argv[0];
	}
	// Input Functions
	void ioHandler(void);
	bool LineInput();
	bool CircleInput();
	bool GenerateSurface();
	bool GenerateBazierSurface();
	bool GenerateSquareCircle();

	// Interpolation functions
	std::vector<Coord> LineGenerator(Coord a1, Coord a2,double );
	std::vector<Coord> GenerateCircle(Coord centre, double radius, double num);
	std::vector<Coord> GenerateEllipse(Coord centre, double radius, double num);
	std::vector<Coord> Bazier(Coord a1, Coord a2, Coord a3, Coord a4,double );
	std::vector<Coord> SquareGenerator(Coord a1, Coord a2, Coord a3, Coord a4, double numV);
	bool generateSurfaceLoft(std::vector<Coord> c1, std::vector<Coord> c2, double numV, Surface& loftSurface);

	// output functions
	bool writeGNU(std::vector<Coord> surface, std::string filename);
	bool displayGNU(std::string programName, std::vector <std::string> dataFiles);
	bool writeGNUSurface(Surface surface, std::string filename);

private:
	Coord p1, p2 ,p3,p4,p5,p6;
	std::vector<Coord> an;
	std::vector<std::string> inFileName;
	std::string programName ;
	std::vector <Surface> surfacesPatch;
};
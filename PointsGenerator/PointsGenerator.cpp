#include "PointsGenerator.h"

bool PointsGenerator::generateSurfaceLoft(std::vector<Coord> c1, std::vector<Coord> c2, double numV, Surface& loftSurface)
{
	if (c1.size() != c2.size())
		return false;
	double deltaV = 1.0 / (numV - 1.0);
	curve c;
	c.resize(c1.size());
	int size = c1.size();
	for (double v = 0; v <= 1.0; v += deltaV)
	{
		for (int i = 0; i < size; i++)
		{
				c[i].x = c1[i].x * (1.0 - v) + c2[i].x * v;
				c[i].y = c1[i].y * (1.0 - v) + c2[i].y * v;
				c[i].z = c1[i].z * (1.0 - v) + c2[i].z * v;

		}
		loftSurface.push_back(c);
	}
	return true;
}

std::vector<Coord> PointsGenerator::LineGenerator(Coord a1, Coord a2,double numV)
{
	double deltaV = 1.0 / (numV - 1.0);

	double tempX = 0.0f, tempY = 0.0f, tempZ = 0.0f, u = 0.0f;
	for (double u = 0; u < 1.0;u+=deltaV)
	{
		tempX = a1.x * (1.0f - u) + a2.x * u;
		tempY = a1.y * (1.0f - u) + a2.y * u;
		tempZ = a1.z * (1.0f - u) + a2.z * u;
		an.push_back({ tempX,tempY,tempZ });
	}
	return an;
}

std::vector<Coord> PointsGenerator::SquareGenerator(Coord a1, Coord a2, Coord a3, Coord a4,double numV)
{
	double deltaV = 1.0 / (numV/4 - 1.0);

	double tempX = 0.0f, tempY = 0.0f, tempZ = 0.0f, u = 0.0f;
		for (double u = 0; u < 1.0; u += deltaV)
		{
			tempX = a1.x * (1.0f - u) + a2.x * u;
			tempY = a1.y * (1.0f - u) + a2.y * u;
			tempZ = a1.z * (1.0f - u) + a2.z * u;
			an.push_back({ tempX,tempY,tempZ });

		/*	tempX = a2.x * (1.0f - u) + a3.x * u;
			tempY = a2.y * (1.0f - u) + a3.y * u;
			tempZ = a2.z * (1.0f - u) + a3.z * u;
			an.push_back({ tempX,tempY,tempZ });

			tempX = a3.x * (1.0f - u) + a4.x * u;
			tempY = a3.y * (1.0f - u) + a4.y * u;
			tempZ = a3.z * (1.0f - u) + a4.z * u;
			an.push_back({ tempX,tempY,tempZ });

			tempX = a4.x * (1.0f - u) + a1.x * u;
			tempY = a4.y * (1.0f - u) + a1.y * u;
			tempZ = a4.z * (1.0f - u) + a1.z * u;
			an.push_back({ tempX,tempY,tempZ });*/
		}
	return an;
}

std::vector<Coord> PointsGenerator::GenerateEllipse(Coord centre, double radius, double num)
{
	std::vector<Coord> circle;
	double deltaTheta = 2.0 * 180.0 / num;
	double tempX = 0.0f, tempY = 0.0f, tempZ = 0.0f;
	for (double i = 0; i < 360.0; i = i + deltaTheta)
	{
		//float angle = (theta * PI) / 180;
		tempX = centre.x + radius * cos(i);
		tempY = centre.y + (radius + 1.5) * sin(i);
		tempZ = centre.z ;
		circle.push_back({ tempX,tempY,tempZ });
	}
	return circle;
}

std::vector<Coord> PointsGenerator::Bazier(Coord a1, Coord a2, Coord a3, Coord a4, double numV)
{
	std::vector<Coord> aN;
	double deltaV = 1.0 / (numV - 1.0);
	double tempX = 0.0f, tempY = 0.0f, tempZ = 0.0f;
	for (double u = 0.0f; u < 1.0f; u = u + deltaV)
	{
		tempX = a1.x * (pow((1 - u), 3)) + 3 * a2.x * (pow((1 - u), 2)) * u + 3 * a3.x * (1 - u) * pow(u, 2) + a4.x * pow(u, 3);
		tempY = a1.y * (pow((1 - u), 3)) + 3 * a2.y * (pow((1 - u), 2)) * u + 3 * a3.y * (1 - u) * pow(u, 2) + a4.y * pow(u, 3);
		tempZ = a1.z * (pow((1 - u), 3)) + 3 * a2.z * (pow((1 - u), 2)) * u + 3 * a3.z * (1 - u) * pow(u, 2) + a4.z * pow(u, 3);

		aN.push_back({ tempX,tempY ,tempZ });
	}
	return aN;
}

std::vector<Coord> PointsGenerator::GenerateCircle(Coord centre, double radius,double num)
{
	std::vector<Coord> circle;
	double deltaTheta = 2.0 * 180.0 / num;
	double tempX=0.0f, tempY=0.0f,tempZ=0.0f;
	for (double i = 0; i < 360.0; i = i+deltaTheta)
	{
		//float angle = (theta * PI) / 180;
		tempX =  centre.x + radius * cos(i);
		tempY =  centre.y + radius * sin(i);
		tempZ =  centre.z  ;
		circle.push_back({ tempX,tempY,tempZ });
	}
	return circle;
}

bool PointsGenerator::LineInput()
{
	programName = "Lines";
	std::ofstream out(inFileName[0]);
	std::cout << "Enter the co-ordinates for the vertex 1: ";
	std::cin >> p1.x >> p1.y >> p1.z;
	std::cout << "Enter the co-ordinates for the vertex 2: ";
	std::cin >> p2.x >> p2.y >> p2.z;
	std::vector<Coord> p3 = LineGenerator(p1, p2,10.0);
	displayGNU(programName, inFileName);

	return true;
}

bool PointsGenerator::CircleInput()
{
	// variable declaration
	double radius = 0.0f;
	double numPoints = 0;
	programName = "Circle";
	std::ofstream out(inFileName[0]);
	p1.x = 2.0f;
	p1.y = 2.0f;
	p1.z = 2.0f;
	radius = 1.0;
	numPoints = 60.0;

	std::vector<Coord> p3 = GenerateCircle(p1,radius,numPoints);
	writeGNU(p3, inFileName[0]);
	displayGNU(programName, inFileName);
	
	return true;
}

bool PointsGenerator::GenerateSurface()
{
	// variable declaration
	double radius = 0.0;
	double numPoints = 0;
	surfacesPatch.resize(9);
	programName = "Circle-Ellipse";
	std::ofstream out(inFileName[0]);
	p1.x = 0.0f;
	p1.y = 0.0f;
	p1.z = 0.0f;
	radius = 2.0;
	numPoints = 60.0;
	std::vector<Coord> p3 = GenerateCircle(p1, radius, numPoints);
	p2.x = 0.0;
	p2.y = 0.0;
	p2.z = 8.0;
	radius = 2.5;
	numPoints = 60.0;
	std::vector<Coord> p4 = GenerateEllipse(p2, radius, numPoints);
   generateSurfaceLoft(p3,p4,numPoints,surfacesPatch[0]);
	writeGNUSurface(surfacesPatch[0], inFileName[0]);
	displayGNU(programName, inFileName);

	return true;
}

bool PointsGenerator::GenerateSquareCircle()
{
	// variable declaration
	double radius = 0.0;
	double numPoints = 15;
	surfacesPatch.resize(9);
	programName = "Circle-Square";
	std::ofstream out(inFileName[0]);

	p1.x = 2.0;
	p1.y = 0.0;
	p1.z = 0.0;

	p2.x = 0.0f;
	p2.y = 2.0f;
	p2.z = 0.0f;

	p3.x = -2.0;
	p3.y = 0.0;
	p3.z = 0.0;

	p4.x = 0.0f;
	p4.y = -2.0f;
	p4.z = 0.0f;
	LineGenerator(p1, p4, numPoints);
	LineGenerator(p4, p3, numPoints);
	LineGenerator(p3, p2, numPoints);
	LineGenerator(p2, p1, numPoints);

	p1.x = 0.0f;
	p1.y = 0.0f;
	p1.z = 8.0f;
	radius = 1.0;
	numPoints = 60.0;
	std::vector<Coord> p3 = GenerateCircle(p1, radius, numPoints);
	generateSurfaceLoft(an, p3, numPoints, surfacesPatch[0]);
	writeGNUSurface(surfacesPatch[0], inFileName[0]);
	displayGNU(programName, inFileName);

	return true;
}

bool PointsGenerator::GenerateBazierSurface()
{
	// variable declaration
	double radius = 0.0;
	double numPoints = 10.0;
	surfacesPatch.resize(9);
	programName = "Bazier-Line";
	std::ofstream out(inFileName[0]);
	p1.x = 0.0f;
	p1.y = 0.0f;
	p1.z = 0.0f;

	p2.x = 4.0f;
	p2.y = 4.0f;
	p2.z = 4.0f;

	std::vector<Coord> p3 = LineGenerator(p1, p2,numPoints);
	p1.x = 1.0;
	p1.y = 2.0;
	p1.z = 1.0;

	p2.x = 2.0f;
	p2.y = 0.0f;
	p2.z = 2.0f;

	p5.x = 3.0f;
	p5.y = 3.0f;
	p5.z = 3.0f;

	p6.x = 4.0f;
	p6.y = 0.0f;
	p6.z = 4.0f;

	std::vector<Coord> p4 = Bazier(p1,p2, p5, p6,numPoints);
	generateSurfaceLoft(p4, p3, numPoints, surfacesPatch[0]);
	//writeGNU(p4, inFileName[0]);
	writeGNUSurface(surfacesPatch[0], inFileName[0]);
	displayGNU(programName, inFileName);

	return true;
}

void PointsGenerator::ioHandler()
{
	int num;
	std::cout << "Enter to plot graph between : \n 1.Lines \n 2.Circle \n 3.Circle-Ellipse \n 4.Bazier-Line \n 5.Square-Circle " << std::endl;
	std::cin >> num;
	switch (num)
	{
	case 1:
		inFileName.push_back("C:\\temp\\Line.dat");
		LineInput();
		break;
	case 2:
		inFileName.push_back("C:\\temp\\Circle.dat");
		CircleInput();
		break;
	case 3:
		inFileName.push_back("C:\\temp\\Circle-Ellipse.dat");
		GenerateSurface();
		break;
	case 4:
		inFileName.push_back("C:\\temp\\Bazier-Line.dat");
		GenerateBazierSurface();
		break;
	case 5:
		inFileName.push_back("C:\\temp\\Square-Circle.dat");
		GenerateSquareCircle();
		break;
	default:
		break;
	}

}

bool PointsGenerator::writeGNU(std::vector<Coord> surface, std::string filename)
{
	std::ofstream outFileHandle;
	outFileHandle.open(filename, std::ios::out | std::ios::trunc);
	outFileHandle << std::fixed << std::setprecision(4);
	int size = surface.size();
	for (int i = 0; i < size; i++)
	{
		outFileHandle << surface[i].x << " " << surface[i].y << " " << surface[i].z << std::endl;
		outFileHandle << std::endl;
	}
	outFileHandle.close();
	return true;
}

bool PointsGenerator::writeGNUSurface(Surface surface, std::string filename)
{
	std::ofstream outFileHandle;
	outFileHandle.open(filename, std::ios::out | std::ios::trunc);
	outFileHandle << std::fixed << std::setprecision(4);
	int size = surface.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			outFileHandle << surface[i][j].x << " " << surface[i][j].y << " " << surface[i][j].z;
			outFileHandle << std::endl;
		}
		outFileHandle << std::endl;
	}
	outFileHandle.close();
	return true;
}

bool PointsGenerator::displayGNU(std::string programName, std::vector <std::string> dataFiles)
{
	std::ofstream outFileHandle;
	outFileHandle.open("gnuScript.plt", std::ios::out | std::ios::trunc);
	outFileHandle << "set title '" << programName << "'" << std::endl;
	outFileHandle << "set view equal xyz" << std::endl;
	outFileHandle << "set view ,,.3" << std::endl;
	//outFileHandle << "set nokey" << endl; 
	outFileHandle << "set hidden3d" << std::endl;
	outFileHandle << "splot ";
	int size = dataFiles.size();
	for (int i = 0; i < size; i++)
	{
		outFileHandle << "'" << dataFiles[i] << "' w l";
		if (i < (size - 1))
			outFileHandle << ",";
	}
	outFileHandle << std::endl << "pause -9 \"Hit Enter\" " << std::endl;
	outFileHandle.close();
	system("wgnuplot.exe gnuScript.plt");
	return true;
}

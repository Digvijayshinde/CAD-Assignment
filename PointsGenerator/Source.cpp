#include "PointsGenerator.h"

int main(int argc,char**argv)
{
	PointsGenerator generate(argv);
	generate.ioHandler();
	return 0;
}
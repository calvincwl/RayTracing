#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	fstream fileOut("../bin/output.ppm", ios::out);
	int nx = 200;
	int ny = 100;
	fileOut << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			int ir = int(255.99f * r);
			int ig = int(255.99f * g);
			int ib = int(255.99f * b);
			fileOut << ir << " " << ig << " " << ib << "\n";
		}
	}
	fileOut.flush();
	fileOut.close();
}
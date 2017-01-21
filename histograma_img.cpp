#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int HISTO[256];

void histograma(char* file) {
	ifstream entrada;
	entrada.open(file);
	int x , y;
	char linea[255];
	entrada.getline(linea,255);
	entrada.getline(linea,255);
	entrada >>  y >> x;
	int R[x][y];
	int G[x][y];
	int B[x][y];
	
	int HR[256];
	int HG[256];
	int HB[256];
	for(int i=0;i<256;i++)
		HR[i]=HG[i]=HB[i]=0;
	
	for(int i =0; i<x; i++)
		for(int j=0; j<y; j++)
		{
			entrada >> R[i][j];
			HR[(R[i][j])]+=1;
			entrada >> G[i][j];
			HG[(G[i][j])]+=1;
			entrada >> B[i][j];
			HB[(B[i][j])]+=1;
		}
	int prom=0;
	for(int i=0; i<256; i++)
	{
			HISTO[i]=(HR[i]+HG[i]+HB[i]) / 3;
	}
}

int main(int argc, char** argv) {
	histograma("orca.ppm");
	for(int i=0; i<256; i++)
	{
			cout << HISTO[i];
	}
}

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

typedef float DECIMAL;
typedef int ENTERO;
typedef char CARACTER;

ENTERO tam= 1000;
ENTERO colors= 256;
void histograma(string file) {
	ifstream entrada;
	entrada.open(file);
	DECIMAL HISTO[tam];

	ofstream salida;
	salida.open("1000vectores_DECIMAL.txt",ios::app);

	ENTERO x , y;

	CARACTER linea[colors];
	 
	entrada.getline(linea,colors);
	entrada >>  x >> y;
	entrada.getline(linea,colors);
	
	ENTERO R[x][y];
	ENTERO G[x][y];
	ENTERO B[x][y];

	DECIMAL HR[colors];
	DECIMAL HG[colors];
	DECIMAL HB[colors];
	for(ENTERO i=0;i<colors;i++)
		HR[i]=HG[i]=HB[i]=0.0;
	for(ENTERO i =0; i<x; i++)
	{
		for(ENTERO j=0; j<y; j++)
		{
			entrada >> R[i][j];
			HR[(R[i][j])]+=1;
			entrada >> G[i][j];
			HG[(G[i][j])]+=1;
			entrada >> B[i][j];
			HB[(B[i][j])]+=1;
		}
	}
	salida << "{";
	for(ENTERO i=0; i<tam; i++)
	{
			DECIMAL prom=0.0;
			prom=(HR[i]+HG[i]+HB[i])/ 3.0;
			HISTO[i]=prom;
			if(i == colors-1)
			{
				salida << HISTO[i];
				break;
			}
			salida << HISTO[i] << ",";
			//cout<<HISTO[i]<<endl;
	}
	salida << "}\n";
	//salida.close();
	//entrada.close();
}

ENTERO main() {

	for(ENTERO i=0; i<tam; i++)
	{
		string str1 = "1000ppm/img"+to_string(i)+".ppm";
		//cout<<str1<<endl;
		histograma(str1);	
	}
	
	//histograma("newimg/img5.ppm");	

	return 0;
}
/*
g++ main.cpp -std=c++11 -lX11 -lpthread -o main
./main
*/

#include "CImg.h"
#include <bits/stdc++.h>

#define f(i,a,b) for(int i=a;i<b;++i)
#define debug(x) cout << #x << " = " << x << endl;
#define see(x) cout<< #x <<" "<<x<< endl;
#define inf 1e6

using namespace std;
using namespace cimg_library;



class Img{
public:
    CImg<float> img;
    vector<float> vec_caract;
    string filename;

    Img(){}
    Img(string nameFile){
        filename = nameFile;
        img.load(nameFile.c_str());
        getCaract();
    }
    ~Img(){}

    void getCaract(){
        vec_caract.push_back( img.mean() );
        vec_caract.push_back( img.min() );
        vec_caract.push_back( img.max() );
        vec_caract.push_back( img.median() );
        vec_caract.push_back( sqrt(img.variance()) ); //desviation

    }

    void display(){
        img.display();
    }

    void print_vec_caract(){
        for ( auto i:vec_caract )        {
            cout<<"V["<<i<<"] "<<i<<endl;
        }
    }
};




int main(){
        Img imagen("parrot_mask.pgm");
        imagen.print_vec_caract();


	return 0;
}
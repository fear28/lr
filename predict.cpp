
#include <iostream>
#include <cmath>
//#include <istream>
//#include <fstream>
#include <cstring>
#include <iomanip>

#include "lr.h"
#include "arg.hpp"
#include "data.hpp"
#include "classification.hpp"

using namespace std;



int main(int argc,char** argv){
	bool dbg=false;
	istream* ist=&cin;
	istream* istp=&cin;
	ostream* ost=&cout;
	ifstream fb;
	ifstream fbp;
	ofstream fw;
	par parametry={0,&dbg,0,0,&ist,&fb,&ost,&fw,0,&istp,&fbp};
	arg(argc,argv,parametry);
	istream in(ist->rdbuf());
	istream inp(istp->rdbuf());
	ostream out(ost->rdbuf());
	double** x;
	int lp;
	int msprz;
	in>>msprz;
	int ww=przygotuj_dane_bez_etykiety(&x,lp,inp,msprz);
	if(fbp){
		fbp.close();
	}
	for(int i=0;i<lp;i++){
		for(int j=0;j<ww;j++){
				cout<<x[i][j]<<" ";
		}
		cout<<endl;
	}
	int ww2;
	in>>ww2;
	if(ww!=ww2){
		cerr<<"Bledny rozmiar"<<endl;
		return -1;
	}
	double* w=new double[ww];
	for(int i=0;i<ww;i++){
		in>>w[i];
	}
	if(fb){
		fb.close();
	}
	int* c=new int[lp];
	classification(c,x,w,ww,lp);

	for(int i=0;i<lp;i++){
		out<<c[i]<<endl;
	}
//	double osg=uczenie(it,x,l,lp,ww,alfa,w,eps,dbg);
	
//	cout<<"Blad: "<<osg<<endl;
//	wypisz(out,w,ww);
	if(fw){
		fw.close();
	}
	delete[] w;
	delete c;
	for(int i=0;i<lp;i++){
		delete[] x[i];
	}
	delete[] x;
	
}

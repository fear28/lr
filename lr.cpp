#include <iostream>
#include <cmath>
//#include <istream>
//#include <fstream>
#include <cstring>
#include <iomanip>

#include "lr.h"
#include "arg.hpp"
#include "data.hpp"
#include "learning.hpp"

using namespace std;



int main(int argc,char** argv){
	int it=1000;
	int msprz=2;
	mnoz mn={msprz,NULL};
	bool dbg=false;
	double alfa=1;
	double eps=0.0001;
	istream* ist=&cin;
	ostream* ost=&cout;
	ifstream fb;
	ofstream fw;
	par parametry={&it,&dbg,&alfa,&eps,&ist,&fb,&ost,&fw,&mn};
	arg(argc,argv,parametry);
	istream in(ist->rdbuf());
	ostream out(ost->rdbuf());
	prost* pro=parametry.m->p;
	int lpro=0;
	while(pro!=NULL){
		lpro++;
		pro=pro->nast;
	}
	double** x;
	int lp;
	int n;
	in>>n;
	in>>lp;
	int* l=new int[lp];
	double** xraw=new double*[lp];
	for(int j=0;j<lp;j++){
		xraw[j]=new double[n];
		in>>l[j];
		for(int i=0;i<n;i++){
			in>>xraw[j][i];
		}
	}
	int ww=przygotuj_dane(&x,lp,xraw,n,mn);
	delete[] xraw;
	if(fb){
		fb.close();
	}
	for(int i=0;i<lp;i++){
		cout<<l[i]<<": ";
		for(int j=0;j<ww;j++){
				cout<<x[i][j]<<" ";
		}
		cout<<endl;
	}
	double* w=new double[ww];
	for(int i=0;i<ww;i++){
		w[i]=0;
	}
	double osg=uczenie(it,x,l,lp,ww,alfa,w,eps,dbg);
	
	cout<<"Blad: "<<osg<<endl;
	wypisz(out,w,ww,mn.msprz,lpro,mn.p);
	if(fw){
		fw.close();
	}
	delete[] w;
	delete[] l;
	for(int i=0;i<lp;i++){
		delete[] x[i];
	}
	delete[] x;
	
}

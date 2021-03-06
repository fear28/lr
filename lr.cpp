#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <thread>

#include "lr.hpp"
#include "arg.hpp"
#include "data.hpp"
#include "learning.hpp"

using namespace std;
using namespace ml;


int main(int argc,char** argv){
	int it=1000;
	int msprz=2;
	mnoz mn={msprz,NULL};
	bool dbg=false;
	int multi=1;
	double alfa=1;
	double eps=0.0001;
	kind_norm norm=L0;
	double beta=0;
	istream* ist=&cin;
	ostream* ost=&cout;
	ifstream fb;
	ofstream fw;
	par parametry={&it,&dbg,&alfa,&eps,&ist,&fb,&ost,&fw,&mn,NULL,NULL,&multi,&norm,&beta};
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
	double osg;
	if(multi==1){
		osg=uczenie(it,x,l,lp,ww,alfa,w,eps,norm,beta,dbg);
	}
	else{
		osg=multi_uczenie(it,x,l,lp,ww,alfa,w,eps,multi,norm,beta,dbg);
	}
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

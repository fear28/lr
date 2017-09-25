#include <iostream>
#include <cmath>
#include <istream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "lr.h"


using namespace std;


void arg(int argc, char** argv, par parametry){
	while(argc>1){
		if(strcmp("-f", argv[1])==0){
			argv++;
			argc--;
			parametry.fb->open(argv[1]);
			if(*(parametry.fb)){
					*(parametry.ist)=parametry.fb;
				}else{
					cerr<<"blad otwarcia pliku"<<endl;
					exit(-1);
				}
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-out", argv[1])==0){
			argv++;
			argc--;
			parametry.fw->open(argv[1]);
			if(*(parametry.fb)){
					*(parametry.out)=parametry.fw;
				}else{
					cerr<<"blad otwarcia pliku"<<endl;
					exit(-1);
				}
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-it", argv[1])==0){
			
			argv++;
			argc--;
			*parametry.it=atoi(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-eps", argv[1])==0){
			
			argv++;
			argc--;
			*parametry.eps=atof(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-msprz", argv[1])==0){
			argv++;
			argc--;
			*parametry.msprz=atoi(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-alfa", argv[1])==0){
			argv++;
			argc--;
			*parametry.alfa=atof(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-Debug", argv[1])==0){
			*parametry.dbg=true;
			argv++;
			argc--;
			continue;
		}
		cerr<<"nieznana opcja: "<<argv[1]<<endl;
		argv++;
		argc--;
	}
}

double uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,bool dbg=false){
	double osg;
	double* b=new double[ww];
	for(int nit=1;nit<=it;nit++){
		for(int i=0;i<ww;i++)
			b[i]=0;
		osg=0;
		for(int i=0;i<lp;i++){
			double a=0;
			for(int j=0;j<ww;j++){
				a+=x[i][j]*w[j];
			}
			double k=1/(1+exp(-a));
			for(int j=0;j<ww;j++){
				b[j]+=alfa*x[i][j]*(k-l[i]);
				osg+=abs(k-l[i]);
			}
			if(dbg)
			cout<<"\tklasa "<<i<<"="<<k<<"~="<<(k>0.5?1:0)<<" powinno="<<l[i]<<endl;
		}
		if(dbg)
			cout<<endl<<"Po itracji "<<nit<<" w={";
		for(int j=0;j<ww;j++){
			w[j]-=b[j];
			if(dbg){
				cout<<w[j];
				if(j!=ww-1) cout<<", ";
			}
		}
		if(dbg){
			cout<<"} "<<endl;
			cout<<"Blad: "<<osg<<endl;
		}
		if(osg<eps) break;
	}
	delete b;
	return osg;
}

void wypisz(ostream& out, double *w,int ww){
	out<<ww<<setprecision(15)<<endl;
	for(int i=0;i<ww;i++){
		out<<w[i]<<" ";
	}
	out<<endl;
} 

int main(int argc,char** argv){
	int it=1000;
	int msprz=2;
	bool dbg=false;
	double alfa=1;
	double eps=0.0001;
	istream* ist=&cin;
	ostream* ost=&cout;
	ifstream fb;
	ofstream fw;
	par parametry={&it,&dbg,&alfa,&eps,&ist,&fb,&ost,&fw,&msprz};
	arg(argc,argv,parametry);
	istream in(ist->rdbuf());
	ostream out(ost->rdbuf());
	int n;
	int lp;
	int ww;
	in>>n;
	in>>lp;
	//ww=n+(n*(n-1))/2+1;
	long int mian=n;
	long int licz=1;
	ww=0;
	int* tabsum=new int[msprz];
	int* tabsumtmp=new int[msprz];
	for(int i=1;i<=msprz;i++){
		ww+=mian/licz;
		tabsum[i-1]=ww+1;
		licz*=(i+1);
		mian*=(n-i);
	}
	ww++;
	
	int* l=new int[lp];
	double** x=new double*[lp];
	for(int i=0;i<lp;i++){
		x[i]=new double[ww];
		in>>l[i];
		x[i][0]=1;
		for(int j=0;j<msprz;j++){
			tabsumtmp[j]=tabsum[j];
		}
		for(int j=1;j<=n;j++){
			in>>x[i][j];
			int a=tabsumtmp[0];
			if(msprz>1){
				for(int k=1;k<j;k++){
					x[i][tabsumtmp[0]++]=x[i][j]*x[i][k];
				}
				for(int k=1;k<msprz-1;k++){
					int tmp=tabsumtmp[k];
		//			cerr<<"a= "<<a<<" tabsum["<<k-1<<"]="<<tabsum[k-1]<<" j= "<<j<<" "<<i<<" "<<tabsum[k-1]<<" "<<tabsumtmp[k]<<endl;
					for(int s=0;s<a-tabsum[k-1];s++)
						x[i][tabsumtmp[k]++]=x[i][j]*x[i][tabsum[k-1]+s];
					a=tmp;
				}
			}
			
		}
	}
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
	wypisz(out,w,ww);
	if(fw){
		fw.close();
	}
}

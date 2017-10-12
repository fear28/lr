#include <iostream>
#include <cmath>
#include <memory>
#include <atomic>
#include "learning.hpp"

void multi_uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,int pocz1,int kon1,int pocz2,int kon2,Barrier* bar,double* b , double volatile* osg,int id, bool dbg=false){
	for(int nit=1;nit<=it;nit++){
		for(int i=pocz1;i<kon1;i++)
			b[i]=0;
		
		for(int i=pocz1;i<kon1;i++){
			double a=0;
			for(int j=0;j<ww;j++){
				a+=x[i][j]*w[j];
			}
			double k=1/(1+std::exp(-a));
			b[i]=k-l[i];
			if(dbg)
				std::cout<<"\tklasa "<<i<<"="<<k<<"~="<<(k>0.5?1:0)<<" powinno="<<l[i]<<std::endl;
		}
		bar->Wait();
		if(id==0){
			*osg=0;
			for(int i=0;i<lp;i++)
				*osg+=std::abs(b[i]);
		}
		if(dbg)
			std::cout<<std::endl<<"Po itracji "<<nit<<" w={";
		for(int j=pocz2;j<kon2;j++){
			for(int i=0;i<lp;i++)
				w[j]-=alfa*x[i][j]*b[i];
			if(dbg){
				std::cout<<w[j];
				if(j!=ww-1) std::cout<<", ";
			}
		}
		if(dbg){
			std::cout<<"} "<<std::endl;
			std::cout<<"Blad: "<<*osg<<std::endl;
		}
		bar->Wait();
		if(*osg<eps) break;
	}
}

double uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,bool dbg=false){
	double osg;
	std::unique_ptr<double[]> b(new double[ww]);
	for(int nit=1;nit<=it;nit++){
		for(int i=0;i<ww;i++)
			b[i]=0;
		osg=0;
		for(int i=0;i<lp;i++){
			double a=0;
			for(int j=0;j<ww;j++){
				a+=x[i][j]*w[j];
			}
			double k=1/(1+std::exp(-a));
			osg+=std::abs(k-l[i]);
			for(int j=0;j<ww;j++){
				b[j]+=alfa*x[i][j]*(k-l[i]);
			}
			if(dbg)
				std::cout<<"\tklasa "<<i<<"="<<k<<"~="<<(k>0.5?1:0)<<" powinno="<<l[i]<<std::endl;
		}
		if(dbg)
			std::cout<<std::endl<<"Po itracji "<<nit<<" w={";
		for(int j=0;j<ww;j++){
			w[j]-=b[j];
			if(dbg){
				std::cout<<w[j];
				if(j!=ww-1) std::cout<<", ";
			}
		}
		if(dbg){
			std::cout<<"} "<<std::endl;
			std::cout<<"Blad: "<<osg<<std::endl;
		}
		if(osg<eps) break;
	}
	return osg;
}

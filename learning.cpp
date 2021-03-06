#include <iostream>
#include <cmath>
#include <memory>
#include <atomic>
#include <thread>

#include "learning.hpp"

namespace ml{

double multi_uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps, int thread=0,kind_norm norm=L0, double beta=0, bool dbg=false){
		if(thread==0){
			thread=std::thread::hardware_concurrency();
			if(thread==0){
				thread=4;
			}
		}
		std::mutex* mutex=new std::mutex();
		Barrier bar(thread);
		double osg;
		double norm_var;
		double* b=new double[lp];
		std::thread t[thread-1];
		for (int i = 0; i < thread-1; ++i) {
			t[i] = std::thread(multi_thread_uczenie,it,x,l,lp,ww,alfa,w,eps,(lp)*i/thread,(lp)*(i+1)/thread,(ww)*i/thread,(ww)*(i+1)/thread,&bar,b,&osg,i,mutex,norm,&norm_var,beta,  dbg);
		}
		multi_thread_uczenie(it,x,l,lp,ww,alfa,w,eps,(lp)*(thread-1)/thread,(lp),(ww)*(thread-1)/thread,(ww),&bar,b,&osg,thread-1,mutex,norm,&norm_var,beta, dbg);
		
		for (int i = 0; i < thread-1; ++i) {
			t[i].join();
		}
		delete[] b;
		return osg;
	
}

void multi_thread_uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,int pocz1,int kon1,int pocz2,int kon2,Barrier* bar,double* b , double * osg,int id,std::mutex* mutex,kind_norm norm, double* norm_var,double beta, bool dbg=false){
	
	for(int nit=1;nit<=it;nit++){
		bar->Wait();
		if(id==0)
			*osg=0;
		double myosg=0;
		for(int i=pocz1;i<kon1;i++){
			double a=0;
			
			for(int j=0;j<ww;j++){
				a+=x[i][j]*w[j];
			}
			double k=1/(1+std::exp(-a));
			b[i]=k-l[i];
			myosg+=std::abs(b[i]);

			if(dbg)
				std::cout<<"\tklasa "<<i<<"="<<k<<"~="<<(k>0.5?1:0)<<" powinno="<<l[i]<<std::endl;
		}
		if(id==0){
			if(norm==L2||norm==Linf){
					*norm_var=0;
				for(int j=0;j<ww;j++){
					if(norm==L2)
						*norm_var+=w[j]*w[j];
					else if(norm==Linf){
						*norm_var=std::abs(w[j])>*norm_var?std::abs(w[j]):*norm_var;
					}
				}
			}
		}
		bar->Wait();
		{
			std::unique_lock<std::mutex> lock{*mutex};
			*osg+=myosg;
		}
		if(dbg)
			std::cout<<std::endl<<"Po itracji "<<nit<<" w={";
		for(int j=pocz2;j<kon2;j++){
			double normj=0;
			if(norm==L1){
				normj=(w[j] > 0) - (w[j] < 0);//sgn(w[j]);
			}else if(norm==L2){
				if(*norm_var!=0)
					normj=w[j]/(std::sqrt(*norm_var));
			}else if(norm==Linf){
				if(std::abs(w[j])==(*norm_var))
					normj=(w[j] > 0) - (w[j] < 0);//sgn(w[j]);
			}
			for(int i=0;i<lp;i++){
				w[j]-=alfa*x[i][j]*b[i];
				
			}
			w[j]-=alfa*beta*normj;
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

double uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,kind_norm norm, double beta, bool dbg=false){
	double osg;
	double norm_var;
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
		
		if(norm==L2||norm==Linf){
			norm_var=0;
			for(int j=0;j<ww;j++){
				if(norm==L2)
					norm_var+=w[j]*w[j];
				else if(norm==Linf){
					norm_var=std::abs(w[j])>norm_var?std::abs(w[j]):norm_var;
				}
			}
			if(dbg)
				std::cout<<"norm_var="<<norm_var<<std::endl;
		}
		if(dbg)
			std::cout<<std::endl<<"Po itracji "<<nit<<" w={";
		for(int j=0;j<ww;j++){
			double normj=0;
			if(norm==L1){
				normj=(w[j] > 0) - (w[j] < 0);//sgn(w[j]);
			}else if(norm==L2){
				if(norm_var!=0)
					normj=w[j]/(std::sqrt(norm_var));
			}else if(norm==Linf){
				if(std::abs(w[j])==(norm_var))
					normj=(w[j] > 0) - (w[j] < 0);//sgn(w[j]);
			}
			w[j]-=b[j]+alfa*beta*normj;
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

}

#include <cmath>

#include "classification.hpp"

void classification(int* c,double** x,double* w,int ww,int lp){
	
		for(int i=0;i<lp;i++){
			double a=0;
			for(int j=0;j<ww;j++){
				a+=x[i][j]*w[j];
			}
			c[i]=(1/(1+std::exp(-a)))>0.5?1:0;
		}
}

#include <iostream>
#include <iomanip>

#include "data.hpp"

void wypisz(std::ostream& out, double *w,int ww){
	out<<ww<<std::setprecision(15)<<std::endl;
	for(int i=0;i<ww;i++){
		out<<w[i]<<" ";
	}
	out<<std::endl;
} 

int przygotuj_dane(double*** xt,int& lp,int** lt,std::istream& in,int msprz){
	int n;
	in>>n;
	in>>lp;
	*lt=new int[lp];
	*xt=new double*[lp];
	double** x=*xt;
	int* l=*lt;
	int* tabsum=new int[msprz];
	int* tabsumtmp=new int[msprz];
	int mian=n;
	int licz=1;
	int ww=0;
	for(int i=1;i<=msprz;i++){
		ww+=mian/licz;
		tabsum[i-1]=ww+1;
		licz*=(i+1);
		mian*=(n-i);
	}
	ww++;
	
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
					for(int s=0;s<a-tabsum[k-1];s++)
						x[i][tabsumtmp[k]++]=x[i][j]*x[i][tabsum[k-1]+s];
					a=tmp;
				}
			}
			
		}
	}
	delete[] tabsum;
	delete[] tabsumtmp;
	return ww;
}

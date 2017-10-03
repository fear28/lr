#include <iostream>
#include <iomanip>

#include "data.hpp"

void wypisz(std::ostream& out, double *w,int ww,int msprz){
	out<<msprz<<" "<<ww<<std::setprecision(15)<<std::endl;
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
	int ww=przygotuj_tabsum(tabsum,msprz,n);
	for(int i=0;i<lp;i++){
		in>>l[i];
		przygotuj_wektor(&x[i],ww,tabsum,tabsumtmp,msprz,n,in);
	}
	delete[] tabsum;
	delete[] tabsumtmp;
	return ww;
}

int przygotuj_dane_bez_etykiety(double*** xt,int& lp,std::istream& in,int msprz){
	int n;
	in>>n;
	in>>lp;
	*xt=new double*[lp];
	double** x=*xt;
	int* tabsum=new int[msprz];
	int* tabsumtmp=new int[msprz];
	int ww=przygotuj_tabsum(tabsum,msprz,n);
	for(int i=0;i<lp;i++){
		przygotuj_wektor(&x[i],ww,tabsum,tabsumtmp,msprz,n,in);
	}
	delete[] tabsum;
	delete[] tabsumtmp;
	return ww;
}


void przygotuj_wektor(double **xt,int ww, int* tabsum,int* tabsumtmp,int msprz,int n,std::istream& in){
	
		*xt=new double[ww];
		double* x=*xt;
		x[0]=1;
		for(int j=0;j<msprz;j++){
			tabsumtmp[j]=tabsum[j];
		}
		for(int j=1;j<=n;j++){
			in>>x[j];
			int a=tabsumtmp[0];
			if(msprz>1){
				for(int k=1;k<j;k++){
					x[tabsumtmp[0]++]=x[j]*x[k];
				}
				for(int k=1;k<msprz-1;k++){
					int tmp=tabsumtmp[k];
					for(int s=0;s<a-tabsum[k-1];s++)
						x[tabsumtmp[k]++]=x[j]*x[tabsum[k-1]+s];
					a=tmp;
				}
			}
			
		}
	
}
int przygotuj_tabsum(int* tabsum,int msprz,int n){

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
	return ww;
}

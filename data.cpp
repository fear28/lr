#include <iostream>
#include <iomanip>

#include "data.hpp"
#include "lr.hpp"

void wypisz(std::ostream& out, double *w,int ww,int msprz,int lpro,prost* p){
	out<<msprz<<" "<<lpro<<std::endl;
	
	while(p!=NULL){
		out<<p->p<<" "<<p->n<<std::endl;
		for(int i=0;i<p->n;i++){
			out<<p->w[i]<<" ";
			
		}
		out<<std::endl;
		for(int i=0;i<p->n;i++){
			
			out<<p->wpod[i]<<" ";
		}
		p=p->nast;
	}
	
	out<<ww<<std::setprecision(15)<<std::endl;
	for(int i=0;i<ww;i++){
		out<<w[i]<<" ";
	}
	out<<std::endl;
} 

int przygotuj_dane(double*** xt,int lp,double** xraw,int n,mnoz m){
	int msprz=m.msprz;
	prost* p=m.p;
	*xt=new double*[lp];
	double** x=*xt;
	int* tabsum=new int[msprz];
	int* tabsumtmp=new int[msprz];
	int ww=przygotuj_tabsum(tabsum,msprz,n);
	ww+=przygotuj_prost(p);
	for(int i=0;i<lp;i++){
		przygotuj_wektor(&x[i],ww,tabsum,tabsumtmp,m,n,xraw[i]);
	}
	delete[] tabsum;
	delete[] tabsumtmp;
	return ww;
}

int przygotuj_prost(prost* p){
	int ret=0;
	while(p!=NULL){
		int a=1;
		for(int i=0;i<p->n;i++){
			a*=p->w[i]-p->wpod[i]+1;
		}
		ret+=a;
		p=p->nast;
	}
	return ret;
}

void wymn(int* podw,int* w,int p,int n,double* x,int it){
	x[it]=1;
	int przes=0;
	int* wtmp=new int[n];
	int* wprzes=new int[n];
	wprzes[0]=1;
	for(int i=0;i<n;i++){
		wtmp[i]=0;
		if(i!=0)
			wprzes[i]=wprzes[i-1]*w[i-1];
	}
	bool kon=false;
	for(;;){
		x[it]*=x[p+przes];
		for(int i=0;i<n;i++){
			wtmp[i]++;
			if(wtmp[i]<podw[i]){
				przes=wtmp[i]*wprzes[i];
				for(int j=0;j<i;j++){
					wtmp[j]=0;
				}
				for(int j=i+1;j<n;j++){
					przes+=wtmp[j]*wprzes[j];

				}
				break;
			}else if(i==n-1){
					kon=true;
					break;
			}
		}
		if(kon==true)
			break;
	}
	delete[] wtmp;
	delete[] wprzes;
}

void przygotuj_wektor(double **xt,int ww, int* tabsum,int* tabsumtmp,mnoz m,int n,double* xraw){
		int msprz=m.msprz;
		*xt=new double[ww];
		double* x=*xt;
		x[0]=1;
		for(int j=0;j<msprz;j++){
			tabsumtmp[j]=tabsum[j];
		}
		for(int j=1;j<=n;j++){
			x[j]=xraw[j-1];
			if(msprz>1){
				int a=tabsumtmp[0];
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
		int it=tabsumtmp[msprz-1];
		prost* pr=m.p;
		while(pr!=NULL){
			int n=pr->n;
			int p=pr->p+1;
			int* wtmp=new int[n];
			int* wprzes=new int[n];
			
			
			wprzes[0]=1;
			for(int i=0;i<n;i++){
				wtmp[i]=0;
				if(i!=0)
					wprzes[i]=wprzes[i-1]*pr->w[i-1];
			}
			int ptmp=p;
			bool kon=false;
			for(;;){
				wymn(pr->wpod,pr->w,ptmp,n,x,it);
				it++;
				for(int i=0;i<n;i++){
					wtmp[i]++;
					if(wtmp[i]<(pr->w[i]-pr->wpod[i]+1)){
						ptmp=p+wtmp[i]*wprzes[i];
						for(int j=0;j<i;j++){
							wtmp[j]=0;
						}
						for(int j=i+1;j<n;j++){
							ptmp+=wtmp[j]*wprzes[j];
						}
					break;
					}else if(i==n-1){
						kon=true;
						break;
					}
				}
				if(kon==true)
					break;
			}
			delete[] wtmp;
			delete[] wprzes;
			pr=pr->nast;
		}
	
}
int przygotuj_tabsum(int* tabsum,int msprz,int n){

	int mian=1;
	int licz=n;
	int ww=0;
	for(int i=1;i<=msprz;i++){
		ww+=licz/mian;
		tabsum[i-1]=ww+1;
		licz*=(n-i);
		mian*=(i+1);
	}
	ww++;
	return ww;
}

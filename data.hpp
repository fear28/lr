#ifndef _DATA_HPP_
#define _DATA_HPP_
#include <iostream>
#include "lr.h"

void wypisz(std::ostream& out, double *w,int ww,int msprz,int lpro,prost* p);

void wymn(int* podw,int* w,int p,int n,double* x,int it);
int przygotuj_dane(double*** xt,int lp,double** xraw,int n,mnoz m);
int przygotuj_tabsum(int* tabsum,int msprz,int n);
int przygotuj_prost(prost* p);
void przygotuj_wektor(double **x,int ww, int* tabsum,int* tabsumtmp,mnoz m,int n,double* xraw);
#endif //_DATA_HPP_

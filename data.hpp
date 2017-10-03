#ifndef _DATA_HPP_
#define _DATA_HPP_
#include <iostream>

void wypisz(std::ostream& out, double *w,int ww,int msprz);

int przygotuj_dane(double*** xt,int& lp,int** lt,std::istream& in,int msprz);
int przygotuj_dane_bez_etykiety(double*** xt,int& lp,std::istream& in,int msprz);
int przygotuj_tabsum(int* tabsum,int msprz,int n);
void przygotuj_wektor(double **x,int ww, int* tabsum,int* tabsumtmp,int msprz,int n,std::istream& in);
#endif //_DATA_HPP_

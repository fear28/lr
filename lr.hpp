#ifndef _LR_H_
#define _LR_H_

#include <istream>
#include <fstream>
#include "learning.hpp"

typedef struct prost{
	prost* nast;
	int p;
	int k;
	int n;
	int* w;
	int* wpod;
} prost;
typedef struct{
	int msprz;
	prost* p;
} mnoz;


typedef struct{
	int* it;
	bool* dbg;
	double* alfa;
	double* eps;
	std::istream** ist;
	std::ifstream* fb;
	std::ostream** out;
	std::ofstream* fw;
//	int* msprz;
	mnoz* m;
	std::istream** istp;
	std::ifstream* fbp;
	int* multi;
	ml::kind_norm* norm;
	double* beta;
} par;

#endif //_LR_H_

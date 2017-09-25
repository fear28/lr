#ifndef _LR_H_
#define _LR_H_

#include <istream>
#include <fstream>

typedef struct{
	int* it;
	bool* dbg;
	double* alfa;
	double* eps;
	std::istream** ist;
	std::ifstream* fb;
	std::ostream** out;
	std::ofstream* fw;
	int* msprz;
} par;

#endif //_LR_H_

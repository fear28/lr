#include "arg.hpp"

#include <cstring>
#include <iostream>

void arg(int argc, char** argv, par parametry){
	while(argc>1){
		if(strcmp("-f", argv[1])==0){
			argv++;
			argc--;
			parametry.fb->open(argv[1]);
			if(*(parametry.fb)){
					*(parametry.ist)=parametry.fb;
				}else{
					std::cerr<<"blad otwarcia pliku"<<std::endl;
					exit(-1);
				}
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-out", argv[1])==0){
			argv++;
			argc--;
			parametry.fw->open(argv[1]);
			if(*(parametry.fb)){
					*(parametry.out)=parametry.fw;
				}else{
					std::cerr<<"blad otwarcia pliku"<<std::endl;
					exit(-1);
				}
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-multi", argv[1])==0){
			argv++;
			argc--;
			*parametry.multi=atoi(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-it", argv[1])==0){
			
			argv++;
			argc--;
			*parametry.it=atoi(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-eps", argv[1])==0){
			
			argv++;
			argc--;
			*parametry.eps=atof(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-msprz", argv[1])==0){
			argv++;
			argc--;
			parametry.m->msprz=atoi(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-prost", argv[1])==0){
			argv++;
			argc--;
			prost* p=new prost;
			p->nast=parametry.m->p;
			parametry.m->p=p;
			p->p=atoi(argv[1]);
			argv++;
			argc--;
			p->k=atoi(argv[1]);
			argv++;
			argc--;
			p->n=atoi(argv[1]);
			argv++;
			argc--;
			p->w=new int[p->n];
			for(int i=0;i<p->n;i++){
				p->w[i]=atoi(argv[1]);
				argv++;
				argc--;
			}
			p->wpod=new int[p->n];
			for(int i=0;i<p->n;i++){
				p->wpod[i]=atoi(argv[1]);
				argv++;
				argc--;
			}
			continue;
		}
		if(strcmp("-alfa", argv[1])==0){
			argv++;
			argc--;
			*parametry.alfa=atof(argv[1]);
			argv++;
			argc--;
			continue;
		}
		if(strcmp("-Debug", argv[1])==0){
			*parametry.dbg=true;
			argv++;
			argc--;
			continue;
		}
		std::cerr<<"nieznana opcja: "<<argv[1]<<std::endl;
		argv++;
		argc--;
	}
}

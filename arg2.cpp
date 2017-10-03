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
		if(strcmp("-fp", argv[1])==0){
			argv++;
			argc--;
			parametry.fbp->open(argv[1]);
			if(*(parametry.fbp)){
					*(parametry.istp)=parametry.fbp;
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
		if(strcmp("-msprz", argv[1])==0){
			argv++;
			argc--;
			*parametry.msprz=atoi(argv[1]);
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

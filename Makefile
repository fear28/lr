CC = g++
CFLAGS= --std=c++11  -g
LIBS= 

all: lr predict

lr: lr.o arg.o data.o learning.o
	$(CC) $(LIBS) lr.o arg.o data.o learning.o -o lr  
lr.o: lr.cpp
	$(CC) $(CFLAGS) lr.cpp -c -o lr.o
arg.o: arg.cpp	
	$(CC) $(CFLAGS) arg.cpp -c -o arg.o
data.o: data.cpp	
	$(CC) $(CFLAGS) data.cpp -c -o data.o
learning.o: learning.cpp	
	$(CC) $(CFLAGS) learning.cpp -c -o learning.o
predict: arg2.o data.o classification.o predict.o
	$(CC) $(LIBS) arg2.o data.o classification.o predict.o -o predict  
arg2.o: arg2.cpp
	$(CC) $(CFLAGS) arg2.cpp -c -o arg2.o
classification.o: classification.cpp
	$(CC) $(CFLAGS) classification.cpp -c -o classification.o
predict.o: predict.cpp
	$(CC) $(CFLAGS) predict.cpp -c -o predict.o 
clean:
	rm -f *.o lr predict

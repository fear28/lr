CC = g++
CFLAGS= --std=c++11 -O2
LIBS= 


lr: lr.o
	$(CC) $(LIBS) lr.o -o lr  
lr.o: lr.cpp
	$(CC) $(CFLAGS) lr.cpp -c -o lr.o
clean:
	rm -f *.o lr

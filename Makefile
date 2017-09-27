CC = g++
CFLAGS= --std=c++11 -O2
LIBS= 


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

clean:
	rm -f *.o lr

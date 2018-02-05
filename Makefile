# 编译c动态链接库的makefile
CC=gcc
SO_FPIC=-fPIC -shared
LIB_NAME=libmain.so


all:libmain test

libmain: 
	$(CC) main.c $(SO_FPIC) -o $(LIB_NAME) 

test:
	$(CC) test.c -L. -lmain -o test

clean:
	rm -rf $(LIB_NAME)
	rm -rf test


export CC=gcc
export CPP=g++

#export CFLAGS= -g -I/usr/local/ssl/include/ -lssl -lcrypto  -ldl -L/usr/local/ssl/lib
export CFLAGS= -g  -lssl -lcrypto  -ldl 


CSRCS = $(wildcard *.c)  
COBJS = $(patsubst %.c, %, $(CSRCS))  
CPPSRCS = $(wildcard *.cpp)  
CPPOBJS += $(patsubst %.cpp, %, $(CPPSRCS))  

OBJ = $(COBJS)
OBJ += $(CPPOBJS)

all: $(OBJ)

%:%.c 
	$(CC) $^ -o $@ $(CFLAGS)

%:%.cpp 
	$(CPP) $^ -o $@ $(CFLAGS)

clean:
	rm *.o $(OBJ)  -rf

.PHONY:clean

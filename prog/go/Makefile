
# optimized compiling
#CC=gcc -O3 -Wall -Wunused -march=native
#LM=-lm
CC=icc -O3 -Wall -Wunused -march=native
LM=

APP=gomdr

all: $(APP)

$(APP): Makefile zcom.h

%:: %.c
	$(CC) -o $@ $< $(LM)

$(APP): alged.h


clean:
	rm -f $(APP) *~ a.out *.dat *.his *.dis *.pos go.e


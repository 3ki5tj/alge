
# optimized compiling
CC=gcc -O3 -Wall -Wunused -march=native
LM=-lm
#CC=icc -O3 -Wall -Wunused -march=native
#LM=

APP=ljmd ljmc

all: $(APP)

$(APP): % : %.c Makefile zcom.h alged.h
	$(CC) -o $@ $< $(LM)

clean:
	rm -f $(APP) *~ a.out *.dat *.his *.dis *.pos *.e


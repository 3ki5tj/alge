
# optimized compiling
CC=gcc -O3 -Wall -Wunused -march=native
LM=-lm
#CC=icc -O3 -Wall -Wunused -march=native
#LM=

APP=xylang xymd xymc

all: $(APP)

$(APP): Makefile zcom.h

%:: %.c
	$(CC) -o $@ $< $(LM)

clean:
	rm -f $(APP) *~ a.out *.dat *.his *.dis *.pos *.e


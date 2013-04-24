
# optimized compiling
#CC=gcc -O3 -Wall -Wunused -march=native
#LM=-lm
CC=icc -O3 -Wall -Wunused 
LM=

app = ljmd ljmc
app_hmc = ljmd_hmc

all: $(app) $(app_hmc)

$(app): % : %.c Makefile zcom.h alged.h
	$(CC) -o $@ $< $(LM)

$(app_hmc): %_hmc : %.c Makefile zcom.h alged.h
	$(CC) -DHMC -o $@ $< $(LM)

clean:
	rm -f $(app) $(app_hmc) *~ a.out *.dat *.his *.dis *.pos *.e


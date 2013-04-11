# optimized compiling
CC=gcc -O3 -Wall -Wunused -march=native
LM=-lm
#CC=icc -O3 -Wall -Wunused -march=native
#LM=

%:: %.c
	$(CC) -o $@ $< $(LM)

subdirs=ispt lj go xy pmer

clean:
	rm -f $(APP) *~ a.out *.dat *.his *.dis *.pos *.e
	-for d in $(subdirs); do ($(MAKE) -C $$d clean); done


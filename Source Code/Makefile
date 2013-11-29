CC=gcc
CFLAGS=-Wall -std=c99 -O2 #-g -pg
SOURCES = pt_utils.c pt_sorting.c pt_gen_timings.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = pt_utils.h pt_sorting.h pt_gen_timings.h

all: $(OBJS)
	$(CC) $(CFLAGS) -o pt_gen_timings $(OBJS) -lm

$(OBJS): $(HEADERS)

.PHONY: clean
clean:
	rm *.o 
	
.PHONY: cleanall
cleanall:
	rm *.o *~ $(EXECS)

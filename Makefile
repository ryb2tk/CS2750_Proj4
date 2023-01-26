GCC = gcc
CFLAGS = -g

findC: findc.o
	$(GCC) $(CFLAGS) findc.o -o findC

findc.o: findc.c findc.h
	$(GCC) $(CFLAGS) -c findc.c findc.h

clean:
	/bin/rm findc.o

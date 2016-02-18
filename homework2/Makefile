CC = /usr/lib64/mpich/bin/mpicc

CFLAGS = -I. -g
LDFLAGS = -L.

default: all 
all: hello potato homework2

.PHONY: clean 

%.o:%.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hello: hello.o
	$(CC) -o $@ $^ $(LDFLAGS)

potato: potato.o
	$(CC) -o $@ $^ $(LDFLAGS)

homework2: homework2.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean: 
	/bin/rm -f *.o hello potato homework2

squeaky: clean
	/bin/rm -f *~ *.bak


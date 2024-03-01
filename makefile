CC=gcc
CFLAGS=-I.
DEPS = header1.h header2.h
OBJ = main.o module1.o module2.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myproject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o myproject

#make myproject
#make clean

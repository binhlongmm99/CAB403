CC=gcc
CPPFLAGS=-I.
DEPS = shm_data.h protoHeader.h
OBJS := shm_reverse_array.o ancillary_functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

shm: $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f *.o
CC=gcc
CPPFLAGS=-lrt -I.
DEPS = sem_data.h funcPrototype.h
OBJS := print_pid.o additional_functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

pidpr: $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f pidpr *.o
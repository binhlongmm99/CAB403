# #==========================EX1=============================
# hellomake: hellomake.c hellofunc.c
# 	gcc -o hellomake hellomake.c hellofunc.c -I.


# #==========================EX2=============================
# CC=gcc
# CFLAGS=-I.
# hellomake: hellomake.o hellofunc.o
# 	$(CC) -o hellomake hellomake.o hellofunc.o


# #==========================EX3=============================
# CC=gcc
# CPPFLAGS=-I.
# DEPS = hellomake.h

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CPPFLAGS)

# hellomake: hellomake.o hellofunc.o 
# 	$(CC) -o hellomake hellomake.o hellofunc.o 


# #==========================EX4=============================
CC=gcc
CPPFLAGS=-I.
DEPS = hellomake.h
OBJ = hellomake.o hellofunc.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)
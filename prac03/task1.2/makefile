OBJS := foo.o bar.o

# link
progName: $(OBJS)
		gcc $(OBJS) -o progName

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.c
		gcc -c $(CFLAGS) $*.c -o $*.o
		gcc -MM $(CFLAGS) $*.c > $*.d

# remove compilation products
clean:
		rm -f progName *.o *.d

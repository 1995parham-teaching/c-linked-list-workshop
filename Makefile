all: cas.out

cas.out: main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm cas.out *.o

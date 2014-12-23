
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
OBJS+=$(patsubst %.cc, %.o, $(wildcard *.cc))

all:$(OBJS)

%.o:%.c
	gcc -O3 -o $@ $^ -g -DDEBUG

clean:
	rm -rf $(OBJS)

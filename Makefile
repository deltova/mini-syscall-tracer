src = $(wildcard src/*.c)
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -g3 -Isrc -Ixlat -Iinclude
obj = $(./xlat/gen.sh) $(src:.c=.o)

myprog: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

PHONY: clean
clean:
	rm -f $(obj) mystrace

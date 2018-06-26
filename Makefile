src = $(wildcard src/*.c)
obj = $(src:.c=.o)

CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -g3 -Isrc -Ixlat -Iinclude

mystrace: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ 
PHONY: clean
clean:
	rm -f $(obj) mystrace

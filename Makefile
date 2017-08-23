SRC = $(wildcard *.c)

CPPFLAGS += -I /home/gec/sqlite3/include
CPPFLAGS += -I /usr/local/jpeg/include

LDFLAGS += -L /home/gec/sqlite3/lib
LDFLAGS += -L /usr/local/jpeg/lib
LDFLAGS += -lsqlite3
LDFLAGS += -ljpeg

BUG += -DDEBUG

CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc

phone_book.out:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

debug.out:$(SRC)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) $(BUG)

clean:
	rm *.out

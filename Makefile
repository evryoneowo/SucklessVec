CC = clang
CFLAGS = -Wall -Wextra -O3
TARGET = libsvec.a
TEST_BIN = test_vec

SRCS = svec.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET) $(TEST_BIN)

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(TEST_BIN): test.o $(TARGET)
	$(CC) $(CFLAGS) -o $@ test.o -L. -lsvec

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(TEST_BIN)

install: $(TARGET)
	mkdir -p /usr/local/include /usr/local/lib
	cp svec.h /usr/local/include/svec.h
	cp $(TARGET) /usr/local/lib/$(TARGET)

.PHONY: all clean install

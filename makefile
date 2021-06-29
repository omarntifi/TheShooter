CFLAGS = -Wall -Wextra  -D _GNU_SOURCE
OUT = TheShooter.exe
CC = gcc
SOURCES = main.c logic/logic.c
OBJECTS = $(SOURCES:.c=.o)

all: $(OUT) clean_o

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUT)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean_o:
	rm $(OBJECTS)

clean:
	rm -f *.o

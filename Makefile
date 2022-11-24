CC       = gcc
CFLAGS   = -Wall -Wextra -O0 -g
OBJFILES = bitmap.o prueba.o
LDFLAGS =

TARGET   = prueba
SOURCES  = prueba.c bitmap.c 
OBJECTS  = $(SOURCES:.c=.o)


.PHONY: all clean re

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@rm -f $(OBJECTS)

clean:
	@rm -f $(TARGET) $(OBJECTS)

re: clean all

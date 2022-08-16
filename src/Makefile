CC =gcc
CFLAGS = -Wall -Werror -Wextra -c
SOURCES = cipher.c module_io.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = ../build/cipher

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

rebuild: all

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm *.o

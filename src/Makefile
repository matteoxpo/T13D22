.PHONY: ci log_ci
CC =gcc
CFLAGS = -Wall -Werror -Wextra -c
BUILD = ../build/
SOURCES =  $(BUILD)cipher.c  $(BUILD)module_io.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE1 = cipher
EXECUTABLE2 = logging_cipher
	
$(EXECUTABLE1): ci
	$(CC) $(OBJECTS) -o $(BUILD)$(EXECUTABLE1)

$(EXECUTABLE2): log_ci
	$(CC) $(OBJECTS) -o $(BUILD)$(EXECUTABLE2)

ci:
	$(CC) -DCIPHER $(CFLAGS) -c cipher.c -o $(BUILD)cipher.o
	$(CC) -DCIPHER $(CFLAGS) -c module_io.c -o $(BUILD)module_io.o

log_ci:
	$(CC) -DLOGGING_CIPHER $(CFLAGS) -c module_io.c -o $(BUILD)module_io.o
	$(CC) -DLOGGING_CIPHER $(CFLAGS) -c logger.c -o $(BUILD)logger.o
	$(CC) -DLOGGING_CIPHER $(CFLAGS) -c cipher.c -o $(BUILD)cipher.o

rebuild: claen all

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm *.o
	-rm  $(BUILD) *.o
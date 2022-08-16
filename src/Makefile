.PHONY: cipher logging_cipher
CC =gcc
CFLAGS = -Wall -Werror -Wextra
BUILD = ../build/
SOURCES =  $(BUILD)cipher.c  $(BUILD)module_io.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE1 = cipher
EXECUTABLE2 = logging_cipher

cipher:
	$(CC) $(CFLAGS) -DCIPHER cipher.c module_io.c -o $(BUILD)$(EXECUTABLE1)

logging_cipher:
	$(CC) $(CFLAGS) -DLOGGING_CIPHER cipher.c logger.c module_io.c -o $(BUILD)$(EXECUTABLE2)

rebuild: claen all

clean:
	-rm *.o
	-rm  $(BUILD)*.o
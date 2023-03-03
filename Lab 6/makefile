CC = gcc
CFLAGS = -Wall -g

# Define the target and the object files
TARGET = LAB6
OBJS = driver.o functions.o

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to build driver.o
driver.o: driver.c functions.h
	$(CC) $(CFLAGS) -c driver.c

# Rule to build functions.o
functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

# Clean rule to remove object files and the target
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

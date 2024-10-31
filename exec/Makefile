CFLAGS = -Wall

# Automatically find all .c files and their corresponding .o files
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Default target
all: final

# Link the object files to create the final executable
final: $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -o final

# Compile .c files to .o files
%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ) final
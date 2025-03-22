CC = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lraylib -lm -lpthread -ldl -lX11
SRCS = game.c draw_board.c piece.c # Add all your source files here
#OBJS = $(SRCS:.c=.o)
EXEC = t  # Change this to your desired output file name

# Rule to build the program
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LDFLAGS)



# Clean up generated files
clean:
	rm -f $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

# Rebuild everything
rebuild: clean $(EXEC)

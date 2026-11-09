CC = gcc
CFLAGS = -Wall -Wextra -no-pie -Werror -std=c99 -g

CLIENT_TARGET = tradeAndReign
CLIENT_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer -lm

JEU_SRC = $(shell find jeu -name "*.c")
SHARED_SRC = $(shell find ../TradeAndReign-shared/ -name "*.c")

CLIENT_MAIN = jeu/main.c
CLIENT_SRC = $(filter-out $(CLIENT_MAIN), $(JEU_SRC)) $(SHARED_SRC)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
CLIENT_MAIN_OBJ = $(CLIENT_MAIN:.c=.o)

all: $(CLIENT_TARGET)

$(CLIENT_TARGET): $(CLIENT_OBJ) $(CLIENT_MAIN_OBJ)
	$(CC) $(CLIENT_OBJ) $(CLIENT_MAIN_OBJ) -o $@ $(CLIENT_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJ) $(CLIENT_MAIN_OBJ)

fclean: clean
	rm -f $(CLIENT_TARGET)

re: fclean all

.PHONY: all clean fclean re

COMPILER        = cc
COMPILER_FLAGS  = -Wall -Wextra -Werror

SERVER     = server.c
CLIENT     = client.c
SERVER_BONUS     = server_bonus.c
CLIENT_BONUS     = client_bonus.c
COMMON_SOURCES  = helper_one.c helper_two.c

SERVER_OBJECTS  = $(SERVER:.c=.o) $(COMMON_SOURCES:.c=.o)
CLIENT_OBJECTS  = $(CLIENT:.c=.o) $(COMMON_SOURCES:.c=.o)

SERVER_BONUS_OBJECTS  = $(SERVER_BONUS:.c=.o) $(COMMON_SOURCES:.c=.o)
CLIENT_BONUS_OBJECTS  = $(CLIENT_BONUS:.c=.o) $(COMMON_SOURCES:.c=.o)

NAME_1     = server
NAME_2     = client

BONUS_1    = server_bonus
BONUS_2    = client_bonus

RM = rm -f

HEADER_FILES = minitalk.h

BONUS_HEADERS = minitalk_bonus.h

all: $(NAME_1) $(NAME_2)

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

$(NAME_1): $(SERVER_OBJECTS) $(HEADER_FILES)
	$(COMPILER) $(COMPILER_FLAGS) $(SERVER_OBJECTS) -o $(NAME_1)

$(NAME_2): $(CLIENT_OBJECTS) $(HEADER_FILES)
	$(COMPILER) $(COMPILER_FLAGS) $(CLIENT_OBJECTS) -o $(NAME_2)

bonus: $(BONUS_1) $(BONUS_2)

$(BONUS_1): $(SERVER_BONUS_OBJECTS) $(BONUS_HEADERS)
	$(COMPILER) $(COMPILER_FLAGS) $(SERVER_BONUS_OBJECTS) -o $(BONUS_1)

$(BONUS_2): $(CLIENT_BONUS_OBJECTS) $(BONUS_HEADERS)
	$(COMPILER) $(COMPILER_FLAGS) $(CLIENT_BONUS_OBJECTS) -o $(BONUS_2)

clean:
	$(RM) $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(SERVER_BONUS_OBJECTS) $(CLIENT_BONUS_OBJECTS)

fclean: clean
	$(RM) $(NAME_1) $(NAME_2) $(BONUS_1) $(BONUS_2)

re: fclean all

.PHONY: all bonus clean fclean re

NAME := ircserv
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 
INCLUDES := -Iinclude
SRC_DIR := src
OBJ_DIR := obj

SRCS := \
	src/Channel.cpp \
	src/Client.cpp \
	src/CommandHandler.cpp \
	src/CommandHandler/handleInvite.cpp \
	src/CommandHandler/handleJoin.cpp \
	src/CommandHandler/handleKick.cpp \
	src/CommandHandler/handleMode.cpp \
	src/CommandHandler/handleNick.cpp \
	src/CommandHandler/handlePass.cpp \
	src/CommandHandler/handlePing.cpp \
	src/CommandHandler/handlePrivmsg.cpp \
	src/CommandHandler/handleTopic.cpp \
	src/CommandHandler/handleUser.cpp \
	src/Bot/Bot.cpp \
	src/Bot/BotCommands.cpp \
	src/Bot/BotMessages.cpp \
	src/Bot/BotPoll.cpp \
	src/IrcMessageTokenizer.cpp \
	src/Server/Server.cpp \
	src/Server/Operations.cpp \
	src/Server/Networking.cpp \
	src/Utils.cpp \
	src/main.cpp \

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $$(dirname $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

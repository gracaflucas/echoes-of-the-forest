NAME = echoes

SRC =	src/main.cpp \
		src/AMonkey.cpp \
		src/Monkey.cpp \
		src/MonkeyNPC.cpp \
		src/Poacher.cpp \
		src/utils.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
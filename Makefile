NAME = ft_containers

SRCS =	main.cpp \

INC	= 	Vector.hpp \
		VectorIterator.hpp \
		Stack.hpp \

OBJS = $(SRCS:.cpp=.o)
OBJS_DIR = .obj

CPP	= clang++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98
RM	= rm -rf

.PHONY:			all clean fclean re

$(OBJS_DIR)/%.o:		%.cpp
						@mkdir -p $(OBJS_DIR)
						$(CPP) $(CPP_FLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(addprefix $(OBJS_DIR)/, $(OBJS)) $(INC)
				$(CPP) $(CPP_FLAGS) $(addprefix $(OBJS_DIR)/, $(OBJS)) -o $(NAME)

clean:
				@$(RM) $(OBJS_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)
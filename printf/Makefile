# Library name
NAME = libftprintf.a

# Source files and object files
SRC = ft_printf.c printf_s.c printf_p.c printf_x.c printf_d.c printf_u.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME) $(OBJ_DIR)

re: fclean all

.PHONY: clean all fclean re
NAME := libftprintf.a
INCLUDES := includes
SRCS := $(patsubst srcs/%, %, $(wildcard srcs/*.c))
OBJ := $(patsubst %.c, %.o, $(SRCS))
FLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -O0

GREEN=\033[0;32m
NC=\033[0m # No Color

VPATH := srcs test
.PHONY: clean re all fclean add_flags debug test

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	@echo "${GREEN}$(NAME) was created ${NC}"

%.o: %.c
	gcc $(FLAGS) -c $(addprefix -I,$(INCLUDES)) $< -o $@

debug: fclean add_flags all
	gcc -lftprintf -L. $(addprefix -I,$(INCLUDES)) test/tests.c $(FLAGS) -o test/ft_printf.out

add_flags:
	$(eval FLAGS = $(DEBUG_FLAGS))

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

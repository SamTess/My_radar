##
## EPITECH PROJECT, 2023
## B-MUL-100
## File description:
## My_radar : makefile
##

NAME_LIB	=		libmy.a

NAME		=		my_radar

OBJ 		=		$(SRC:.c=.o)

SRC2		=		src/main.c

SRC			=		$(shell find . -type f -name '*.c')

CSFML		=		-lcsfml-graphics -lcsfml-system	\
					-lcsfml-audio -lcsfml-window -lm

all:	$(NAME_LIB)

$(NAME_LIB):$(OBJ)
	ar rc $(NAME_LIB) $(OBJ)
	gcc -g $(OBJ) -o $(NAME) -Wall -Wextra $(CSFML)

clean:
		rm -f $(NAME)

fclean: clean
		rm -f $(OBJ)
		rm -f $(NAME_LIB)

re : fclean all

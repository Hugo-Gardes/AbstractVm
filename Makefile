##
## EPITECH PROJECT, 2021
## B-PDG-300-MPL-3-1-PDGD04am-hugo.gardes
## File description:
## Makefile
##

C++	=	g++

NAME	=	abstractVM

SRC		=	$(wildcard *.cpp)
SRC		+=	$(wildcard sources/*.cpp)
SRC		+=	$(wildcard sources/headers/*.cpp)

RM	=	rm -f

CPPFLAGS	=	-std=c++2a -W -Wall -Wextra -g3 -I ./headers
# CPPFLAGS	+=	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

all:	$(NAME)

$(NAME):
	$(C++) -o $(NAME) $(SRC) $(CPPFLAGS)

clean:
	$(RM) *~
	$(RM) #*#

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

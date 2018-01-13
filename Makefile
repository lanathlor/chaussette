##
## Makefile for GofLife in /home/aragon_m/CPE_colle_semaine7
## 
## Made by My-Lan Aragon
## Login   <aragon_m@epitech.net>
## 
## Started on  Tue Jun  7 19:00:26 2016 My-Lan Aragon
## Last update Fri Dec 23 14:52:12 2016 vivier valentin
##

CP		= cp

CC		= gcc -g3

RM		= rm -rf

MKDIR		= mkdir

NAME		= interpreteur

NAME_TEST   = lol

LIBS 		= lib/my/gnl.c \
		  lib/my/my_putstr.c \
		  lib/my/my_strlen.c \
		  lib/my/my_perror.c \
		  lib/my/my_strcmp.c \
		  lib/my/free_tab.c \
		  lib/my/my_strcpy.c \
		  lib/my/my_getnbr.c \
		  lib/my/my_putnbr.c \
		  lib/my/my_revstr.c \
		  lib/my/my_getstr.c \
		  lib/my/my_putbase.c \
		  lib/my/my_strcat.c \
		  lib/my/tab_malloc.c \
		  lib/my/my_hashstr.c \
		  lib/my/my_strtowordtab.c

LIPS 		= src_Lipsite/talkative.c \
		  src_Lipsite/Lipsite.c

SRCS		= src_Chaussette/tool.c \
		  src_Chaussette/usable.c \
		  src_Chaussette/findVar.c \
		  src_Chaussette/findType.c \
		  src_Chaussette/equal.c \
		  src_Chaussette/parseer.c \
		  src_Chaussette/builtIn.c \
		  src_Chaussette/Operat.c \
		  src_Chaussette/getFunc.c \
		  src_Chaussette/condHandle.c \
		  src_Chaussette/getVar.c \
		  src_Chaussette/getALLvar.c

MAIN_TEST 		= main_test.c

MAIN 			= main.c

OBJS		= $(SRCS:.c=.o) \
			  $(LIPS:.c=.o) \
			  $(LIBS:.c=.o) \
			  $(MAIN:.c=.o)

OBJS_TEST	= $(SRCS:.c=.o) \
			  $(LIPS:.c=.o) \
			  $(LIBS:.c=.o) \
			  $(MAIN_TEST:.c=.o)

#CFLAGS		+= -W -Wall -Werror -Wextra

CFLAGS		+= -Iincludes -Ilib/my

all		: $(NAME)

$(NAME)		: $(OBJS)
		  $(CC) $(OBJS) -o $(NAME)

test		: $(OBJS_TEST)
		  $(CC) $(OBJS_TEST) -o $(NAME_TEST)

clean		:
		  $(RM) $(OBJS)
		  $(RM) $(OBJS_TEST)

fclean		: clean
		  $(RM) $(NAME)

re		: fclean all

.PHONY		: all clean fclean re

CC		= gcc -g3

RM		= rm -rf

GIT 		= git

CP 		= cp -rf

MKDIR		= mkdir

NAME		= chaussette

NAME_TEST 	= lol

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

SRCS		= src_Chaussette/external.c \
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
		  src_Chaussette/getALLvar.c \
		  src_Chaussette/isJustInt.c

MAIN_TEST 		= main/main_test.c

MAIN 			= main/main.c

OBJS		= $(SRCS:.c=.o) \
			  $(LIPS:.c=.o) \
			  $(LIBS:.c=.o) \
			  $(MAIN:.c=.o)

OBJS_TEST	= $(SRCS:.c=.o) \
			  $(LIPS:.c=.o) \
			  $(LIBS:.c=.o) \
			  $(MAIN_TEST:.c=.o)

CFLAGS		+= -W -Wall -Werror -Wextra

CFLAGS		+= -Iincludes -Ilib/my

all		: $(NAME)

$(NAME)		: $(OBJS)
		  $(CC) $(OBJS) -o $(NAME)

test		: $(OBJS_TEST)
		  $(CC) $(OBJS_TEST) -o $(NAME_TEST)

install 	: re
		  $(CP) $(NAME) /bin
		  $(CP) $(NAME) /usr/bin
		  $(CP) $(NAME) /usr/sbin

uninstall 	: fclean
		  $(RM) /bin/$(NAME)
		  $(RM) /usr/bin/$(NAME)
		  $(RM) /usr/sbin/$(NAME)

update		:
		  $(GIT) pull

push 		:
		  $(GIT) add --all
		  $(GIT) commit -am "new"
		  $(GIT) push

clean		:
		  $(RM) $(OBJS)
		  $(RM) $(OBJS_TEST)

fclean		: clean
		  $(RM) $(NAME)
		  $(RM) $(NAME_TEST)

re		: fclean all

.PHONY		: all clean fclean re

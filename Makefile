CC		= gcc -g3

RM		= rm -rf

GIT 		= git

CP 		= cp -rf

MKDIR		= mkdir

NAME		= chaussette

NAME_TEST 	= lol

NAME_COMPIL 	= compilator

NAME_INT 	= int

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
		  src_Chaussette/isJustInt.c \
		  src_Chaussette/getValue.c

MAIN_TEST 		= main/main_test.c

MAIN 			= main/interpreter.c

MAIN_COMP 		= main/ChaussetteCompiler.c

MAIN_INT 		= main/ReadComp.c

OBJS		= $(SRCS:.c=.o) \
			  $(LIPS:.c=.o) \
			  $(LIBS:.c=.o)

OBJS_MAIN	= $(MAIN:.c=.o)

OBJS_TEST	= $(MAIN_TEST:.c=.o)

OBJS_COMP	= $(MAIN_COMP:.c=.o)

OBJS_INT	= $(MAIN_INT:.c=.o)


CFLAGS		+= -W -Wall -Werror -Wextra -fPIC

CFLAGS		+= -Iincludes -Ilib/my

$(NAME)		: $(OBJS) $(OBJS_MAIN)
		  $(CC) $(OBJS) $(OBJS_MAIN) $(CFLAGS) -o $(NAME)

all		: $(NAME) test comp int linked

test		: $(OBJS_TEST) $(OBJS)
		  $(CC) $(OBJS) $(OBJS_TEST) $(CFLAGS) -o $(NAME_TEST)

comp		: $(OBJS_COMP) $(OBJS)
		  $(CC) $(OBJS) $(OBJS_COMP) $(CFLAGS) -o $(NAME_COMPIL)

int		: $(OBJS_INT) $(OBJS)
		  $(CC) $(OBJS) $(OBJS_INT) $(CFLAGS) -o $(NAME_INT)

linked 		: $(OBJS)
		  $(CC) $(OBJS) $(CFLAGS) -o lib$(NAME).so -shared -fPIC
		  $(CC) $(OBJS) $(CFLAGS) -o lib$(NAME).so.1 -shared -fPIC

install 	: re linked
		  $(CP) $(NAME) /bin
		  $(RM) /usr/include/chaussette
		  $(MKDIR) /usr/include/chaussette
		  $(CP) Makefile /usr/include/chaussette/.
		  $(CP) src_Chaussette /usr/include/chaussette/src_Chaussette
		  $(CP) src_Lipsite /usr/include/chaussette/src_Lipsite
		  $(CP) includes/*.h /usr/include/chaussette/.
		  $(CP) lib /usr/include/chaussette/lib
		  $(CP) main/interpreter.c /usr/include/chaussette/.
		  $(CP) includes/Chaussette.h /usr/include/.
		  $(CP) libchaussette.so* /usr/include/chaussette/.
		  $(CP) libchaussette.so* /usr/lib/.
		  $(CP) libchaussette.so* /lib/.
		  $(CP) $(NAME) /usr/bin
		  $(CP) $(NAME) /usr/sbin
		  ldconfig

uninstall 	: fclean
		  $(RM) /bin/$(NAME)
		  $(RM) /usr/include/chaussette
		  $(RM) /usr/include/chaussette.h
		  $(RM) /usr/bin/$(NAME)
		  $(RM) /usr/lib/libchaussette.so*
		  $(RM) /lib/libchaussette.so
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
		  $(RM) $(OBJS_MAIN)
		  $(RM) $(OBJS_INT)
		  $(RM) $(OBJS_COMP)

fclean		: clean
		  $(RM) $(NAME)
		  $(RM) lib$(NAME).so
		  $(RM) lib$(NAME).so.1
		  $(RM) $(NAME_TEST)
		  $(RM) $(NAME_COMPIL)
		  $(RM) $(NAME_INT)

re		: fclean $(NAME)

.PHONY		: all clean fclean re

CC 		= g++

RM 		= rm

SRCS 		= 	src/main.c \
			src/item.cpp

OBJS 		= $(SRCS:.c=.o)

CPPFLAGS 	= -Iinclude -lchaussette

CFLAGS 		= -W -Wall -Wextra

NAME 		= test

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) -o $(NAME)
clean :
	$(RM) $(OBJS)
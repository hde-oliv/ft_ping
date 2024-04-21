SRC		:=	main.c parse.c debug.c run.c packet.c

INC_DIR :=	headers
SRC_DIR :=	sources
OBJ_DIR :=	objects

INCS	:=	$(INC_DIR)
SRCS	:=	$(addprefix $(SRC_DIR)/,$(SRC))
OBJS    :=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC		:=	clang
NAME	:=	ft_ping

CFLAGS	+=	-Wall -Wextra -Werror
LFLAGS  +=	-I.
TFLAGS	+=	-fsanitize=address -g
RM		:=	rm -rf


all:		obj $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)/$(INCS)

$(NAME):	$(OBJS)
			$(CC) -lm -o cz $(NAME) $(OBJS)
# @sudo setcap cap_net_raw+eip ./ft_ping

obj:
			@mkdir -p $(OBJ_DIR)

clean:
			$(RM) $(OBJS) $(OBJ_DIR)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re obj

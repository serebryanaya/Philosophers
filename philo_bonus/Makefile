NAME			= philo_bonus

HEAD_DIR		= inc/
HEADER			= philo_bonus.h

OPTFLAGS		= -O2
CC				= cc

CFLAGS			= -Wall -Wextra -Werror $(OPTFLAGS)
#CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address $(OPTFLAGS)

SRC_DIR			= src/

SRCS			= eat_bonus.c \
				init_and_check_bonus.c \
				main_bonus.c \
				print_bonus.c \
				standart_bonus.c \
				utils_bonus.c

OBJ				= $(patsubst %.c,%.o,$(SRCS))

OBJ_DIR			= obj/

OBJS			= $(addprefix $(OBJ_DIR), $(OBJ))

all:			$(NAME)

bonus:			$(NAME)

$(NAME):		$(OBJS) Makefile
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c $(HEAD_DIR)$(HEADER)
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@ -I $(HEAD_DIR)

RM				= rm -Rf

clean:
				$(RM) $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus

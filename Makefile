NAME = cub3D

red             = /bin/echo -e "\x1b[31m\#\# $1\x1b[0m"
green           = /bin/echo -e "\x1b[32m\#\# $1\x1b[0m"
yellow          = /bin/echo -e "\x1b[33m\#\# $1\x1b[0m"
blue            = /bin/echo -e "\x1b[34m\#\# $1\x1b[0m"
purple          = /bin/echo -e "\x1b[35m\#\# $1\x1b[0m"

FILES = main events get_next_line get_next_line_utils player init raycasting

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRC_DIR = src/
OBJ_DIR = obj/

INCLUDE = 	-I ./include -Imlx 
CC = cc
CFLAGS = -Wall -Wextra -Werror $(DEBUG)
DEBUG = -g3 
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF):
	@mkdir -p $(OBJ_DIR)

# ---------------------------------- RULES ----------------------------------- #

all:  $(NAME) $(LIBFT)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
	@$(CC) $(CFLAGS) $(MLX_LIB) $(LIBFT) $(OBJS) $(MLX_FLAGS) $(INCLUDE) -o $@
	@$(call blue,"✅ $@ build successful!")
 
$(OBJ_DIR)%.o : %.c Makefile | $(OBJF)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@$(call blue,"✅ $< compiled!")


$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR) --no-print-directory
	@$(call blue,"✅ $@ compiled!")

$(MLX_LIB):
	@make -C $(MLX_DIR) --no-print-directory
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@$(call blue,"🗑️  $(NAME) cleaned")

fclean: 
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@make clean
	@rm -f $(NAME)
	@make clean -C $(MLX_DIR) --no-print-directory
	@$(call blue,"🗑️  $(NAME) fcleaned")

re:
	@make fclean 
	@make all
	@$(call blue,"🗑️  $(NAME) fcleaned")


vpath %.c $(SRC_DIR) $(SRC_DIR)gnl

.PHONY: all clean fclean re


NAME = cub3D
FILES = main events get_next_line  get_next_line_utils player

SRC_DIR = src/
OBJ_DIR = obj/

INCLUDE = 	-I ./include -Imlx 
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF):
	@mkdir -p $(OBJ_DIR)

vpath %.c $(SRC_DIR) $(SRC_DIR)gnl $(SRC_DIR)raycaster

.PHONY: all clean fclean re

all:  $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	cc $(CFLAGS) $(MLX_LIB) $(OBJS) $(MLX_FLAGS) $(INCLUDE) -o $@
 
$(OBJ_DIR)%.o : %.c Makefile | $(OBJF)
	cc $(CFLAGS) $(INCLUDE) -c $< -o $@


$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	
fclean: 
	make clean
	rm -f $(NAME)
	@make clean -C $(MLX_DIR)

re:
	make fclean 
	make all
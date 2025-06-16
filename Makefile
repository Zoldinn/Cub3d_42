NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g

DIR_SRC = srcs
SRC = $(addprefix $(DIR_SRC)/, main.c \
	parsing/check_map_file.c \
	parsing/map_parsing.c \
	parsing/map_parsing_utils.c \
	utils/utils.c \
	utils/utils2.c \
	utils/frees.c \
	utils/init_and_close.c \
	rendering/map.c \
	rendering/render_mini_map.c \
	rendering/render_map.c \
	rendering/ray_draw.c \
	raycast/camera.c \
	raycast/raycasting.c)

DIR_OBJ = objs
OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

DIR_LIBFT = libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_MLX = mlx
MLX = $(DIR_MLX)/libmlx_Linux.a
MLX_FLAGS = -I$(DIR_MLX) -L$(DIR_MLX) -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "🔨 Compilation de $(NAME)..."
	@cc $(OBJ) $(LIBFT) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) -lm
	@echo "✅ Compilation réussie !"

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c | $(DIR_OBJ)
	@echo "🔧 Compilation de $<..."
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(LIBFT):
	@echo "📦 Compilation de libft..."
	@make -s -C $(DIR_LIBFT) > /dev/null 2>&1

$(MLX):
	@echo "📦 Compilation de la MiniLibX..."
	@make -s -C $(DIR_MLX) > /dev/null 2>&1
# "> /dev/null 2>&1" pour pas avoir les msg degueu de compil

clean:
	@echo "🧹 Nettoyage des fichiers .o ..."
	@rm -rf $(DIR_OBJ)
	@make -s -C $(DIR_LIBFT) clean
	@make -s -C $(DIR_MLX) clean > /dev/null 2>&1
	@echo "✅ Nettoyage terminé !"


fclean: clean
	@echo "🗑️ Suppression de $(NAME)..."
	@rm -f $(NAME)
	@make -s -C $(DIR_LIBFT) fclean
	@echo "✅ Tout a été supprimé !"

re: fclean all

.PHONY: all clean fclean re

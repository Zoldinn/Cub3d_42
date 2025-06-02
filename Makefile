NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g

DIR_SRC = srcs
SRC = $(addprefix $(DIR_SRC)/, main.c \
	utils/utils.c \
	utils/utils2.c \
	utils/frees.c \
	paring/check_map_file.c \
	paring/map_parsing.c \
	paring/map_parsing_utils.c)

DIR_OBJ = objs
OBJ = $(addprefix $(DIR_OBJ)/, $(notdir $(SRC:.c=.o)))

DIR_LIBFT = libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_MLX = mlx
MLX = $(DIR_MLX)/libmlx_Linux.a
MLX_FLAGS = -I$(DIR_MLX) -L$(DIR_MLX) -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "🔨 Compilation de $(NAME)..."
	@cc $(OBJ) $(LIBFT) $(CFLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Compilation réussie !"

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c | $(DIR_OBJ)
	@echo "🔧 Compilation de $<..."
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

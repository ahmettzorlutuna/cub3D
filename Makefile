# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 21:25:23 by azorlutu          #+#    #+#              #
#    Updated: 2025/10/30 17:45:35 by ekibar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
RM = rm -rf

NAME = cub3d

# --- DİZİNLER ---
SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./objs/
LIB_DIR = ./lib/

# --- KÜTÜPHANELER ---
LIBFT_PATH = $(LIB_DIR)libft/
LIBFT = $(LIBFT_PATH)libft.a

MLX_PATH    = $(LIB_DIR)minilibx-linux/
MLX = $(MLX_PATH)libmlx.a

# --- KAYNAK DOSYALARI ---
SRC = main.c \
		parser/parser_utils.c \
		parser/parser.c \
		parser/parse_color.c \
		parser/gnl/get_next_line.c \
		parser/gnl/get_next_line_utils.c \
		parser/handle_map_line.c \
		parser/parse_textures.c \
		parser/parse_color_utils.c \
		parser/finalize_map.c \
		utils/init_game.c \
		utils/error.c \
		utils/memory.c \
		parser/flood_fill.c \
		parser/duplicate_grid.c \
		engine/render.c \
		hooks/hooks.c \
		hooks/hooks_helpers.c \
		hooks/move_player.c \
		hooks/rotate_player.c \
		hooks/setup_player_vectors.c \
		engine/raycast_dda.c \
		engine/raycast_draw.c \
		engine/raycast_init.c \
		engine/raycast_project.c \
		engine/window.c \
		engine/textures.c

SRCS    = $(addprefix $(SRC_PATH), $(SRC))
OBJ     = $(SRC:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))

# --- FLAG'LER ---
INC = -I $(INC_PATH) -I $(LIBFT_PATH) -I $(MLX_PATH)
# Kütüphane Yolları (-L) ve Kütüphane Adları (-l)
LFLAGS = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx
MLXFLAGS = -lXext -lX11 -lm -lz

# --- RENKLER ---
COLOR_RESET='\033[0m'
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_YELLOW='\033[0;33m'
COLOR_PURPLE='\033[0;35m'

# --- KURALLAR ---
all: $(OBJ_PATH) $(LIBFT) $(MLX) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

# .c dosyalarını .o dosyalarına derler
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(dir $@) # Alt klasörleri otomatik oluştur
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(PURPLE)Compiled:$(RESET) $<"

# --- HATA BURADAYDI, DOĞRU SIRALAMA BUDUR ---
# Önce derlenmiş .o dosyaları, sonra kütüphane yolları ve adları,
# en son -o ile programın adı verilir.
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) ready!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(MLX):
	@echo "$(PURPLE)Making MiniLibX...$(RESET)"
	@make -C $(MLX_PATH)

clean:
	@$(RM) $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC $(LIBFT_PATH)

re: fclean all

.PHONY: all re clean fclean

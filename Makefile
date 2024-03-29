# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 18:19:29 by vrichese          #+#    #+#              #
#    Updated: 2019/07/19 14:02:29 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

SOURCE_DIR	= source
GNL_DIR		= get_next_line
LIBFT_DIR	= $(GNL_DIR)/libft
PRINTF_DIR	= ft_printf
MLX_DIR		= minilibx_macos

MLX_INCLUDE	= usr/local/include
GNL_INCL	= $(GNL_DIR)/includes
LIBFT_INCL	= $(LIBFT_DIR)/includes
PRINTF_INCL	= $(PRINTF_DIR)/includes
INCLUDES	= -I./$(GNL_INCL) -I./$(LIBFT_INCL) -I./$(PRINTF_INCL) -I./includes

LIBFTPRINTF	= $(PRINTF_DIR)/libftprintf.a
LIBFT		= $(GNL_DIR)/libft/libft.a
MLX_LIB		= $(MLX_DIR)/libmlx.a

FILES		= $(addprefix $(SOURCE_DIR)/, fdf.c errors_handler.c lists_functions.c read_and_write_coordinates.c linear_algebra.c hint.c display_pixels.c key_handler.c mouse_handler.c)

OBJ_FILES	= ${FILES:%.c=%.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(LIBFTPRINTF) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(INCLUDES) $(GNL_DIR)/source/get_next_line.c $^ -o $@

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -I./$(MLX_INCLUDE) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

$(LIBFTPRINTF):
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(PRINTF_DIR) clean

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re:	fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 17:48:36 by dicosta-          #+#    #+#              #
#    Updated: 2025/07/18 13:45:48 by dicosta-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_strlen.c ft_strncmp.c ft_strchr.c ft_strrchr.c ft_strnstr.c\
			ft_strlcpy.c ft_strlcat.c ft_strdup.c ft_toupper.c ft_tolower.c\
				ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c\
					ft_calloc.c ft_atoi.c ft_bzero.c ft_substr.c ft_strjoin.c\
						ft_strtrim.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c\
							ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_split.c ft_striteri.c\
								ft_printf.c ft_printf_utils.c ft_isspace.c ft_strcmp.c ft_strcpy.c\

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c	ft_lstclear.c	ft_lstiter.c ft_lstmap.c \

OBJ = $(SRC:.c=.o)
BOBJ = $(SRC_BONUS:.c=.o)
NAME = libft.a

all: $(NAME)
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ) $(BOBJ)
	@touch bonus
	@rm bonus

fclean: clean
	@rm -f $(NAME) 

re: fclean all

bonus: $(BOBJ) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(BOBJ)
	@touch bonus

.PHONY : all clean fclean re

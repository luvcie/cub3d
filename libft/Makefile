# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 19:31:51 by lucpardo          #+#    #+#              #
#    Updated: 2025/05/14 01:08:43 by lucpardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
AR = ar rc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_isalpha.c \
	ft_printf.c \
	ft_printf_helpers.c \
	ft_printf_more_helpers.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_strdup.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_calloc.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_substr.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strjoin.c \
	ft_itoa.c \
	ft_split.c \

SRCS_BONUS = ft_lstnew_bonus.c \
			 ft_lstadd_front_bonus.c \
			 ft_lstsize_bonus.c \
			 ft_lstlast_bonus.c \
			 ft_lstadd_back_bonus.c \
			 ft_lstdelone_bonus.c \
			 ft_lstclear_bonus.c \
			 ft_lstiter_bonus.c \
			 ft_lstmap_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "libft.a built!"

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME) $(OBJS_BONUS)
		$(AR) $(NAME) $(OBJS_BONUS)
		@echo "libft.a built with bonus functions!"

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@echo "objects vacuumed!"

fclean: clean
	rm -f $(NAME)
	@echo "libft.a is gone!"

re: fclean all

.PHONY: all clean fclean re bonus

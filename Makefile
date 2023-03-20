# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 09:32:52 by brheaume          #+#    #+#              #
#    Updated: 2023/03/20 15:39:16 by brheaume         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SERVER_NAME = server
CLIENT_NAME = client

SSRC = server.c
CSRC = client.c

CC = clang
CFLAGS = -Wextra -Werror -Wall -o

LIBFT = libft.a
LIBDIR = libft/

all: libft client server

client:
	$(CC) $(CSRC) $(LIBDIR)$(LIBFT) $(CFLAGS) $(CLIENT_NAME)

server:
	$(CC) $(SSRC) $(LIBDIR)$(LIBFT) $(CFLAGS) $(SERVER_NAME)

clean:
	rm -f $(LIBDIR)*.o

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	rm -f $(LIBDIR)$(LIBFT)

libft:
	$(MAKE) -C $(LIBDIR)

.PHONY: all libft client server clean fclean

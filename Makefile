# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 09:32:52 by brheaume          #+#    #+#              #
#    Updated: 2023/03/09 13:37:57 by brheaume         ###   ########.fr        #
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

libft:
	$(MAKE) -C $(LIBDIR)

.PHONY: all libft client server

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 09:32:52 by brheaume          #+#    #+#              #
#    Updated: 2023/03/29 13:00:26 by brheaume         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SERVER_NAME = server
CLIENT_NAME = client

SSRC = server.c
CSRC = client.c
SOBJ = $(SSRC:.c=.o)
COBJ = $(CSRC:.c=.o)

CC = clang
CFLAGS = -Wextra -Werror -Wall

LIBFT = libft.a
LIBDIR = libft/

all: libft client server

client: $(COBJ)
	$(CC) $(CFLAGS) $(COBJ) $(LIBDIR)$(LIBFT) -o $(CLIENT_NAME)

server: $(SOBJ)
	$(CC) $(CFLAGS) $(SOBJ) $(LIBDIR)$(LIBFT) -o $(SERVER_NAME)

clean:
	rm -f $(LIBDIR)*.o

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	rm -f $(LIBDIR)$(LIBFT)

libft:
	$(MAKE) -C $(LIBDIR)

.PHONY: all libft clean fclean

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/05 00:34:51 by rabougue          #+#    #+#              #
#    Updated: 2017/11/05 01:01:57 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -sf ./Makefile.Matt_daemon
	@make -sf ./Makefile.Ben_AFK

Matt_daemon:
	@make -sf ./Makefile.Matt_daemon

Ben_AFK:
	@make -sf Makefile.Ben_AFK

clean:
	@make clean -sf ./Makefile.Matt_daemon
	@make clean -sf ./Makefile.Ben_AFK

fclean:
	@make fclean -sf ./Makefile.Matt_daemon
	@make fclean -sf ./Makefile.Ben_AFK

re: clean all

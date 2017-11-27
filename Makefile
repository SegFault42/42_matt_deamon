##################################_COMPILATION_#################################
NAME	= Matt_deamon
CC		= clang++
FLAG	= 
SRCS	=	./source/main.cpp\
			./source/deamon.cpp\
			./source/Tintin_reporter.cpp

OBJS	= $(SRCS:.c=.o)

INCLUDE	= -I ./include

###########################_RELINK_MODIFY_.h####################################
RELINK = ./include/MattDaemon.h
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAG) $(INCLUDE) -o $(NAME) $(OBJS)
	@printf "✅  Compilation done. (serveur)\n"

clean:
	@printf "                                                               \r"
	@printf "✅  clean done !\n"
	@rm -f $(NAME)


re: clean all

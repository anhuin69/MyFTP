##
##
##

SERVER_NAME		=	serveur

SERVER_SRCS    		=	./ftp_server/srcs/main.c			\
				./ftp_server/srcs/ftp_server.c			\
				./ftp_server/srcs/server_error.c		\
				./ftp_server/srcs/fork_client.c			\
				./ftp_server/srcs/swrite.c			\
				./ftp_server/srcs/sread.c			\
				./ftp_server/srcs/client_request.c		\
				./ftp_server/srcs/xmalloc.c			\
				./ftp_server/srcs/build_real_path.c		\
				./ftp_server/srcs/load_lexer.c			\
				./ftp_server/srcs/ftp_command_acces.c		\
				./ftp_server/srcs/ftp_command_move.c		\
				./ftp_server/srcs/ftp_command_file.c		\
				./ftp_server/srcs/ftp_command_transfert.c	\
				./ftp_server/srcs/ftp_data.c			\
				./ftp_server/srcs/ftp_cmd_retr.c		\
				./ftp_server/srcs/ftp_cmd_stor.c		\
				./ftp_server/srcs/ftp_cmd_list.c		\
				./ftp_server/srcs/xfunc.c

SERVER_OBJS			=	$(SERVER_SRCS:.c=.o)
SERVER_INCL			=	-I./ftp_server/headers

####################################################

CLIENT_NAME		=	client

CLIENT_SRCS		=	./ftp_client/srcs/main.c				\
				./ftp_client/srcs/ftp_client.c				\
				./ftp_client/srcs/prompt.c				\
				./ftp_client/srcs/execute_request.c			\
				./ftp_client/srcs/client_error.c			\
				./ftp_client/srcs/swrite.c				\
				./ftp_client/srcs/sread.c				\
				./ftp_client/srcs/epure_str.c				\
				./ftp_client/srcs/xmalloc.c				\
				./ftp_client/srcs/load_client_lexer.c			\
				./ftp_client/srcs/client_command.c			\
				./ftp_client/srcs/count_parameters.c			\
				./ftp_client/srcs/client_command_transfert.c		\
				./ftp_client/srcs/client_command_list.c			\
				./ftp_client/srcs/ftp_data.c				\
				./ftp_client/srcs/client_active_mode.c			\
				./ftp_client/srcs/client_command_get.c			\
				./ftp_client/srcs/client_command_put.c			\
				./ftp_client/srcs/auth_me_dude.c			\
				./ftp_client/srcs/local_cmd.c

CLIENT_OBJS			=	$(CLIENT_SRCS:.c=.o)
CLIENT_INCL			=	-I./ftp_client/headers

####################################################

CC			=	gcc
RM			=	rm -f
CFLAGS			=	-W -Wall -Wextra -Werror 

#####################################################

.c.o	:
	@$(CC) $(CFLAGS) $(SERVER_INCL) $(CLIENT_INCL) -c $< -o $@
	@printf " \033[34m[Compilation]\033[39m %s\n" $<

all	:	$(SERVER_OBJS) $(CLIENT_OBJS)
		@$(CC) $(SERVER_OBJS) -o $(SERVER_NAME)
		@printf "\n \033[33m[Message]\033[39m Server compilation under Linux done\n\n"
		@$(CC) $(CLIENT_OBJS) -o $(CLIENT_NAME)
		@printf "\n \033[33m[Message]\033[39m Client compilation under Linux done\n\n"

clean	:
	@$(RM) *~ $(SERVER_OBJS)
	@printf " \033[31m[Delete] \033[39m%s\n" $(SERVER_OBJS)
	@$(RM) *~ $(CLIENT_OBJS)
	@printf " \033[31m[Delete] \033[39m%s\n" $(CLIENT_OBJS)

fclean	:	clean
	@$(RM) $(SERVER_NAME)
	@$(RM) $(CLIENT_NAME)
	@printf "\n \033[31m[Delete] \033[39m%s\n\n" $(NAME)

re	:	fclean all

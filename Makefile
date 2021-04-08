SHELL 	= 	/bin/sh

CC 	= 	gcc

NAME 	= 	myftp

ROOT 	= 	.

SRC_DIR 	= 	$(ROOT)/sources

BUILD_DIR 	= 	$(ROOT)/build


SRC 	= 	main.c 					 				\
			print_usage.c 			 				\
			server.c 	 			 				\
			utils.c 				 				\
			read_command.c 	 		 				\
			functions/login.c 		 				\
			functions/noop.c 		 				\
			add_new_client.c 		 				\
			functions/pwd.c			 				\
			functions/client_errors.c 				\
			functions/change_dir.c 					\
			functions/passive_mode.c 				\
			functions/retr.c 						\
			functions/stor.c 						\
			functions/data_transfer_error.c 		\
			functions/delete.c 		 				\
			functions/list_directory.c 		 		\
			functions/active_mode.c 				\

SRCS 	= 	$(addprefix $(SRC_DIR)/, $(SRC))

OBJS 	= 	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CFLAGS 	= 	-I $(ROOT)/includes -g

WARN 	= 	-W -Wall -Wextra


# Colors

GREY=\x1b[30m

RED=\x1b[31m

GREEN=\x1b[32m

YELLOW=\x1b[33m

BLUE=\x1b[34m

PURPLE=\x1b[35m

CYAN=\x1b[36m

WHITE=\x1b[37m

END=\x1b[0m


.SILENT:

all: $(NAME)

$(BUILD_DIR):
	@echo -e "$(BLUE)Create build directory$(END)"
	mkdir -p $(BUILD_DIR)/functions

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo -e "$(GREEN)Compile sources$(END)"
	@echo -e "$(GREEN)Links objects$(END)"
	$(CC) -o $@ $(CFLAGS) $(WARN) $(OBJS)

clean:
	@echo -e "$(RED)Deletes tmp$(END)"
	rm -rf vg*
	rm -rf $(OBJS)
	rm -rf $(BUILD_DIR)

fclean: clean
	@echo -e "$(RED)Deletes binary$(END)"
	rm -rf $(NAME)

re: fclean all
	@echo -e "$(YELLOW)Recompile$(END)"

.PHONY: all clean fclean re

SHELL 	= 	/bin/sh

CC 	= 	gcc

NAME 	= 	myftp

TEST_NAME 	= 	unit_tests

ROOT 	= 	.

SRC_DIR 	= 	$(ROOT)/sources

BUILD_DIR 	= 	$(ROOT)/build

TEST_DIR 	= 	$(ROOT)/tests

BUILD_TEST_DIR 	= 	$(ROOT)/test_build

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

TEST_SRC 	= 	tests.c 	\

SRCS 	= 	$(addprefix $(SRC_DIR)/, $(SRC))

OBJS 	= 	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TEST_SRCS 	= 	$(addprefix $(TEST_DIR)/, $(TEST_SRC))

TEST_OBJS 	= 	$(patsubst $(TEST_DIR)/%.c, $(BUILD_TEST_DIR)/%.o, $(TEST_SRCS))

CFLAGS 	= 	-I $(ROOT)/includes -g

LDFLAGS 	= 	-lcriterion --coverage

WARN 	= 	-W -Wall -Wextra

TMP 	= 	*.gc* 	\
			vg* 	\

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

tests_run: CFLAGS += -D __TESTS_RUN__

tests_run: $(TEST_NAME)
	./$(TEST_NAME)

$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_NAME): $(TEST_OBJS) $(OBJS)
	@echo -e "$(GREEN)Compile sources$(END)"
	@echo -e "$(GREEN)Compile unit tests$(END)"
	@echo -e "$(GREEN)Links objects$(END)"
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(WARN) $(OBJS) $(TEST_OBJS)

$(NAME): $(OBJS)
	@echo -e "$(GREEN)Compile sources$(END)"
	@echo -e "$(GREEN)Links objects$(END)"
	$(CC) -o $@ $(CFLAGS) $(WARN) $(OBJS)

clean:
	@echo -e "$(RED)Deletes tmp$(END)"
	rm -rf $(TMP)
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_TEST_DIR)

fclean: clean
	@echo -e "$(RED)Deletes binary$(END)"
	rm -rf $(NAME)
	rm -rf $(TEST_NAME)

re: fclean all
	@echo -e "$(YELLOW)Recompile$(END)"

.PHONY: all clean fclean re

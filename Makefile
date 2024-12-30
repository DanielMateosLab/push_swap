CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibs/libft/include

NAME = push_swap
BUILD_DIR = build
TEST_OUT = test/build

SRCS = src/main.c src/stack_lifecycle.c src/stack_operations.c src/stack_utils.c \
		src/stack_utils_2.c src/args_parsing.c src/actions.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
HEADER = include/push_swap.h

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft

$(OBJS): $(HEADER)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	+make -C $(LIBFT_DIR) > /dev/null

clean:
	rm -rf $(BUILD_DIR)
	+make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

deb: CFLAGS += -g3 -fsanitize=address
deb: re

leaks: CFLAGS += -g3
leaks: re

# TODO automaticaly detect if it's mac or linux and run leaks or valgrind
run_leaks_mac: leaks
	leaks --atExit -q -- ./$(NAME)

test:
	mkdir -p $(TEST_OUT)
	cd $(TEST_OUT) && cmake ..
	+make -C $(TEST_OUT)
	cd $(TEST_OUT) && ctest --output-on-failure

test_clean:
	rm -rf $(TEST_OUT)

test_re: test_clean test

.PHONY: all clean fclean re deb leaks run_leaks_mac test test_clean test_re

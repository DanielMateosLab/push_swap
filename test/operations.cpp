#include "gtest/gtest.h"
#include <fstream>
#include <string>

extern "C" {
#include "push_swap.h"
}

char	*stack_to_string(t_stack *stack)
{
	char	*result;
	size_t	i;
	char	*num_str;

	result = ft_strdup("");
	i = stack->base;
	while (i != stack->top)
	{
		num_str = ft_itoa(stack->stack[i]);
		result = ft_strjoin(result, num_str);
		free(num_str);
		result = ft_strjoin(result, " ");
		i = stack_index(stack, i, NEXT);
	}
	num_str = ft_itoa(stack->stack[stack->top]);
	result = ft_strjoin(result, num_str);
	free(num_str);
	return (result);
}

class StackTest : public ::testing::Test {
protected:
	t_stack a;
	t_stack b;

	void TearDown() override {
		stack_destroy(&a);
		stack_destroy(&b);
	}
};

TEST_F(StackTest, StackInitEmpty) {
	stack_init_empty(&a, 10);

	ASSERT_EQ(a.top, 0);
	ASSERT_EQ(a.base, 0);
	ASSERT_EQ(a.taken, 0);
	ASSERT_EQ(a.capacity, 10);
}

TEST_F(StackTest, StackInitFromNumbers) {
	char **numbers = ft_split("5 4 3 2 1", ' ');
	char *str_stack;

	stack_init_from_nums(&a, numbers);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "1 2 3 4 5");

	free(str_stack);
	str_array_clear(numbers);
}

TEST_F(StackTest, StackIndex) {
	stack_init_empty(&a, 5);
	// Fill with 3 nums, test operations
	a.stack[0] = 1;
	a.stack[1] = 2;
	a.stack[2] = 3;
	a.top = 2;
	a.base = 0;
	a.taken = 3;

	ASSERT_EQ(stack_index(&a, 0, NEXT), 1);
	ASSERT_EQ(stack_index(&a, 0, PREV), 2);
	ASSERT_EQ(stack_index(&a, 1, NEXT), 2);
	ASSERT_EQ(stack_index(&a, 1, PREV), 0);
	ASSERT_EQ(stack_index(&a, 2, NEXT), 0);
	ASSERT_EQ(stack_index(&a, 2, PREV), 1);
}

TEST_F(StackTest, Swap) {
	char **numbers = ft_split("1 2", ' ');

	stack_init_from_nums(&a, (char **)numbers);
	ASSERT_EQ(a.stack[a.top], 1);
	stack_swap(&a);

	ASSERT_EQ(a.stack[a.top], 2);
	ASSERT_EQ(a.stack[a.base], 1);

	str_array_clear(numbers);
}

TEST_F(StackTest, Push) {
	char **numbers = ft_split("1 2", ' ');

	stack_init_from_nums(&a, (char **)numbers);
	stack_init_empty(&b, 2);
	stack_push(&b, &a);

	ASSERT_EQ(a.stack[a.top], 2);
	ASSERT_EQ(b.stack[b.top], 1);

	str_array_clear(numbers);
}

TEST_F(StackTest, Rotate) {
	char **numbers = ft_split("1 2 3", ' ');
	char *str_stack;

	stack_init_from_nums(&a, numbers);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	stack_rotate(&a);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "2 1 3");
	free(str_stack);

	stack_rotate(&a);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "1 3 2");
	free(str_stack);

	stack_rotate(&a);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_array_clear(numbers);

}

TEST_F(StackTest, ReverseRotate) {
	char **numbers = ft_split("1 2 3", ' ');
	char *str_stack;

	stack_init_from_nums(&a, numbers);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	stack_reverse_rotate(&a);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "1 3 2");
	free(str_stack);

	stack_reverse_rotate(&a);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "2 1 3");
	free(str_stack);

	stack_reverse_rotate(&a);
	str_stack = stack_to_string(&a);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_array_clear(numbers);
}

/*
class SaveBeginTest : public ::testing::Test {
protected:
	char **map;

	void SetUp() override {
		map = read_map(path);
	}

	void TearDown() override {
		str_array_clear(map);
	}
};

TEST_F(SaveBeginTest, ReadMapOk) {
	ASSERT_NE(map, nullptr);
}

TEST_F(SaveBeginTest, ReadLength) {
	ASSERT_EQ(map_length(map), 11);
}

TEST_F(SaveBeginTest, ReadsMapContent) {
    std::ifstream file(path);
    ASSERT_TRUE(file.is_open()) << "Failed to open the file.";

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        ASSERT_STREQ(map[i], line.c_str()) << "Mismatch on line " << i;
        i++;
    }

    file.close();
}

TEST(NullReturn, WrongPath) {
	const char path[] = "wrong_path";
	ASSERT_EQ(read_map(path), nullptr);
}

TEST(EmptyMap, NonNullPtr) {
	const char path[] = "../../maps/empty.ber";
	char **map = read_map(path);
	ASSERT_NE(map, nullptr);
	str_array_clear(map);
}
*/

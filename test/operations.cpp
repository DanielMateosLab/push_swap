#include "gtest/gtest.h"
#include <fstream>
#include <string>

extern "C" {
#include "push_swap.h"
}

class StackTest : public ::testing::Test {
protected:
	t_stack a;
	t_stack b;

	void SetUp() override {
		ft_bzero(&a, sizeof(t_stack));
		ft_bzero(&b, sizeof(t_stack));
	}

	void TearDown() override {
		stack_destroy(&a);
		stack_destroy(&b);
	}
};

TEST_F(StackTest, StackInitFromNumbers) {
	char **numbers = ft_split("5 4 3 2 1", ' ');
	char *str_stack;

	stack_init_from_nums(&a, numbers);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "1 2 3 4 5");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "5 4 3 2 1");
	free(str_stack);

	str_array_clear(numbers);
}

TEST_F(StackTest, SwapLen2) {
	char **numbers = ft_split("1 2", ' ');
	char *str_stack;

	stack_init_from_nums(&a, (char **)numbers);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2");
	free(str_stack);

	stack_swap(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "1 2");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "2 1");
	free(str_stack);

	str_array_clear(numbers);
}

TEST_F(StackTest, SwapLen3) {
	char **numbers = ft_split("1 2 3", ' ');
	char *str_stack;

	stack_init_from_nums(&a, (char **)numbers);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2 3");
	free(str_stack);

	stack_swap(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "3 1 2");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "2 1 3");
	free(str_stack);

	str_array_clear(numbers);
}

TEST_F(StackTest, SwapLen5) {
	char **numbers = ft_split("1 2 3 4 5", ' ');
	char *str_stack;

	stack_init_from_nums(&a, (char **)numbers);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "5 4 3 2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2 3 4 5");
	free(str_stack);

	stack_swap(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "5 4 3 1 2");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "2 1 3 4 5");
	free(str_stack);

	str_array_clear(numbers);
}

TEST_F(StackTest, PushFromTwoToEmpty) {
	char **numbers = ft_split("1 2", ' ');

	stack_init_from_nums(&a, (char **)numbers);
	stack_push(&b, &a);

	ASSERT_EQ(a.top->content, 2);
	ASSERT_EQ(a.top->prev, (void *)NULL);
	ASSERT_EQ(a.top->next, (void *)NULL);
	ASSERT_EQ(a.base->prev, (void *)NULL);
	ASSERT_EQ(a.base->next, (void *)NULL);
	ASSERT_EQ(a.size, (size_t)1);

	ASSERT_EQ(b.top->content, 1);
	ASSERT_EQ(b.top->prev, (void *)NULL);
	ASSERT_EQ(b.top->next, (void *)NULL);
	ASSERT_EQ(b.base->prev, (void *)NULL);
	ASSERT_EQ(b.base->next, (void *)NULL);
	ASSERT_EQ(b.size, (size_t)1);

	str_array_clear(numbers);
}

TEST_F(StackTest, PushFromOneToEmpty) {
    char **numbers = ft_split("1", ' ');

    stack_init_from_nums(&a, (char **)numbers);
    stack_push(&b, &a);

    ASSERT_EQ(a.top, (void *)NULL);
    ASSERT_EQ(a.base, (void *)NULL);
    ASSERT_EQ(a.size, (size_t)0);

    ASSERT_EQ(b.top->content, 1);
    ASSERT_EQ(b.top->prev, (void *)NULL);
    ASSERT_EQ(b.top->next, (void *)NULL);
    ASSERT_EQ(b.base->prev, (void *)NULL);
    ASSERT_EQ(b.base->next, (void *)NULL);
    ASSERT_EQ(b.size, (size_t)1);

    str_array_clear(numbers);
}

TEST_F(StackTest, PushFromFilledToFilled) {
    char **a_numbers = ft_split("1 2", ' ');
    char **b_numbers = ft_split("3 4", ' ');

    stack_init_from_nums(&a, (char **)a_numbers);
    stack_init_from_nums(&b, (char **)b_numbers);
    stack_push(&b, &a); // B will be 1 3 4

	ASSERT_EQ(a.size, (size_t)1);
	ASSERT_EQ(b.size, (size_t)3);

	ASSERT_EQ(a.base->content, 2);
	ASSERT_EQ(a.top->content, 2);

	ASSERT_EQ(b.top->content, 1);
	ASSERT_EQ(b.base->content, 4);
	ASSERT_EQ(b.base->next->content, 3);
	ASSERT_EQ(b.base->next->next->content, 1);
	ASSERT_EQ(b.base->next->next->next, (void *)NULL);
	ASSERT_EQ(b.base->prev, (void *)NULL);
	ASSERT_EQ(b.base->next->prev, b.base);
	ASSERT_EQ(b.top->next, (void *)NULL);
	ASSERT_EQ(b.top->prev, b.base->next);

    str_array_clear(a_numbers);
    str_array_clear(b_numbers);
}


TEST_F(StackTest, ReverseRotate) {
	char **numbers = ft_split("1 2 3", ' ');
	char *str_stack;

	stack_init_from_nums(&a, numbers);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2 3");
	free(str_stack);

	stack_reverse_rotate(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "2 1 3");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "3 1 2");
	free(str_stack);

	stack_reverse_rotate(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "1 3 2");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "2 3 1");
	free(str_stack);

	stack_reverse_rotate(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2 3");
	free(str_stack);

	str_array_clear(numbers);

}

TEST_F(StackTest, Rotate) {
	char **numbers = ft_split("1 2 3", ' ');
	char *str_stack;

	stack_init_from_nums(&a, numbers);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2 3");
	free(str_stack);

	stack_rotate(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "1 3 2");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "2 3 1");
	free(str_stack);

	stack_rotate(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "2 1 3");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "3 1 2");
	free(str_stack);

	stack_rotate(&a);
	str_stack = stack_to_string(&a, 1);
	ASSERT_STREQ(str_stack, "3 2 1");
	free(str_stack);

	str_stack = stack_to_string(&a, -1);
	ASSERT_STREQ(str_stack, "1 2 3");
	free(str_stack);

	str_array_clear(numbers);
}

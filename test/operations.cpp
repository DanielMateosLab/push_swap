#include "gtest/gtest.h"
#include <fstream>
#include <string>

extern "C" {
#include "push_swap.h"
}

std::string stack_to_string(const t_stack& stack) {
    std::string result;
    for (int i = stack.base; i <= stack.top; i++) {
        result += std::to_string(stack.stack[i]);
        if (i < stack.top) {
            result += " ";
        }
    }
    return result;
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

	ASSERT_EQ(a.top, -1);
	ASSERT_EQ(a.base, 0);
	ASSERT_EQ(a.taken, 0);
	ASSERT_EQ(a.capacity, 10);
}

TEST_F(StackTest, StackInitFromNumbers) {
	char **numbers = ft_split("5 4 3 2 1", ' ');

	stack_init_from_nums(&a, (char **)numbers);
	ASSERT_EQ(stack_to_string(a), "1 2 3 4 5");

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
	stack_push(&a, &b);

	ASSERT_EQ(a.stack[a.top], 2);
	ASSERT_EQ(b.stack[b.top], 1);
}

TEST_F(StackTest, Rotate) {
	char **numbers = ft_split("1 2 3", ' ');

	stack_init_from_nums(&a, (char **)numbers);
	stack_rotate(&a);
	ASSERT_EQ(stack_to_string(a), "3 1 2");
	stack_rotate(&a);
	ASSERT_EQ(stack_to_string(a), "2 3 1");
	stack_rotate(&a);
	ASSERT_EQ(stack_to_string(a), "1 2 3");

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

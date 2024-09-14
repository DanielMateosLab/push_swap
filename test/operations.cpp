#include "gtest/gtest.h"
#include <fstream>
#include <string>

extern "C" {
#include "push_swap.h"
}

TEST(Swap, Swap) {
	t_stack a;
	char **numbers = ft_split("1 2", ' ');

	stack_init_from_nums(&a, (char **)numbers);
	ASSERT_EQ(a.stack[a.top], 1);
	stack_swap(&a);

	ASSERT_EQ(a.stack[a.top], 2);
	ASSERT_EQ(a.stack[a.base], 1);

	str_array_clear(numbers);
	stack_destroy(&a);
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

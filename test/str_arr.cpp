#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cstring>

extern "C" {
#include "so_long.h"
}

class StrArrayCopyTest : public ::testing::TestWithParam<std::vector<std::string>> {
protected:
    std::vector<char*> input_array;
    std::vector<char*> result_array;

    void SetUp() override {
        const auto& params = GetParam();
        input_array = createStringArray(params);
    }

    void TearDown() override {
        freeStringArray(input_array);
        freeStringArray(result_array);
    }

    std::vector<char*> createStringArray(const std::vector<std::string>& strings) {
        std::vector<char*> arr;
        arr.reserve(strings.size() + 1);
        for (const auto& str : strings) {
            arr.push_back(strdup(str.c_str()));
        }
        arr.push_back(nullptr);
        return arr;
    }

    void freeStringArray(std::vector<char*>& arr) {
        for (char* str : arr) {
            free(str);
        }
        arr.clear();
    }
};

TEST_P(StrArrayCopyTest, CopyArrayCorrectly) {
    const auto& params = GetParam();

    char** result = str_array_copy(input_array.data());
    ASSERT_NE(result, nullptr);

    // Convert result back to vector for easier management
    for (int i = 0; result[i] != nullptr; ++i) {
        result_array.push_back(result[i]);
    }
    result_array.push_back(nullptr);
    free(result);  // Free the array itself, but not its contents

    EXPECT_EQ(result_array.size(), input_array.size());

    for (size_t i = 0; i < params.size(); ++i) {
        ASSERT_NE(result_array[i], nullptr);
        EXPECT_STREQ(result_array[i], params[i].c_str());
        EXPECT_NE(result_array[i], input_array[i]);  // Ensure deep copy
    }
    EXPECT_EQ(result_array[params.size()], nullptr);
}

INSTANTIATE_TEST_SUITE_P(
    VaryingArraySizes,
    StrArrayCopyTest,
    ::testing::Values(
        std::vector<std::string>{},  // Empty array
        std::vector<std::string>{"Hello"},  // Single element
        std::vector<std::string>{"Hello", "World"},  // Two elements
        std::vector<std::string>{"One", "Two", "Three", "Four", "Five"}  // Multiple elements
    )
);

TEST(StrArrayCopyNullTest, CopyNullArray) {
    char** result = str_array_copy(NULL);
    EXPECT_EQ(result, nullptr);
}

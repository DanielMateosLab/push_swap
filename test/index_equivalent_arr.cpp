#include "gtest/gtest.h"
#include <fstream>
#include <string>

extern "C" {
#include "push_swap.h"
}

TEST(IndexEquivalentArrTest, BasicArray) {
    int arr[] = {4, 2, 1, 3};
    int expected[] = {3, 1, 0, 2};
    int* result = get_index_equivalent_arr(arr, 4);

    ASSERT_NE(result, nullptr);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(result[i], expected[i]);
    }
    free(result);
}

TEST(IndexEquivalentArrTest, SingleElement) {
    int arr[] = {42};
    int expected[] = {0};
    int* result = get_index_equivalent_arr(arr, 1);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], expected[0]);
    free(result);
}

TEST(IndexEquivalentArrTest, NegativeNumbers) {
    int arr[] = {-3, -1, -4, -2};
    int expected[] = {1, 3, 0, 2};
    int* result = get_index_equivalent_arr(arr, 4);

    ASSERT_NE(result, nullptr);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(result[i], expected[i]);
    }
    free(result);
}

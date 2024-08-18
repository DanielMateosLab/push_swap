#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <tuple>
#include <regex>

extern "C" {
#include "so_long.h"
}

std::string extractAndCleanFileName(const std::string& path) {
    // Regex pattern explanation:
    // ([^/\\]+)  - Capture group 1: Match one or more characters that are not / or \
    // (?=        - Positive lookahead (don't consume characters)
    //   \.       - Match a literal dot
    //   [^.]+    - Match one or more characters that are not dots
    //   $        - End of string
    // )          - End of lookahead
    std::regex pattern(R"(([^/\\]+)(?=\.[^.]+$))");

    std::smatch matches;
    if (std::regex_search(path, matches, pattern)) {
        std::string fileName = matches[1].str();

        // Remove underscores
        fileName.erase(std::remove(fileName.begin(), fileName.end(), '_'), fileName.end());

        return fileName;
    }

    return ""; // Return empty string if no match found
}

struct SaveBeginTestParams {
    const char* path;
    int expected_begin_x;
    int expected_begin_y;
};

class SaveBeginTest : public ::testing::TestWithParam<SaveBeginTestParams> {
protected:
	char **map;

	void SetUp() override {
		map = read_map(GetParam().path);
	}

	void TearDown() override {
		str_array_clear(map);
	}
};

TEST_P(SaveBeginTest, ReadMapOk) {
	const auto& params = GetParam();
	t_point	begin;

	ASSERT_NE(map, nullptr);
	save_begin(map, &begin);
	ASSERT_EQ(begin.x, params.expected_begin_x);
	ASSERT_EQ(begin.y, params.expected_begin_y);
}

INSTANTIATE_TEST_SUITE_P(
	SaveBeginTests,
	SaveBeginTest,
	::testing::Values(
		SaveBeginTestParams{"../../maps/42.ber", 1, 3},
		SaveBeginTestParams{"../../maps/map2.ber", 1, 4}
	)
);

struct HasExitTestParams {
    const char* path;
    int expected_result;
};

class HasExitTest : public ::testing::TestWithParam<HasExitTestParams> {
protected:
	char **map;

	void SetUp() override {
		map = read_map(GetParam().path);
	}

	void TearDown() override {
		str_array_clear(map);
	}
};

TEST_P(HasExitTest, HasExit) {
	const auto& params = GetParam();
	int result = has_exit(map, ft_strlen(map[0]), str_array_len(map));
	ASSERT_EQ(result, params.expected_result);
}

INSTANTIATE_TEST_SUITE_P(
	HasExitTests, HasExitTest,
	::testing::Values(
		HasExitTestParams{"../../maps/42.ber", 1},
		HasExitTestParams{"../../maps/map.ber", 1},
		HasExitTestParams{"../../maps/map2.ber", 1},
		HasExitTestParams{"../../maps/map3.ber", 1},
		HasExitTestParams{"../../maps/map4.ber", 1},
		HasExitTestParams{"../../maps/map5.ber", 1},
		HasExitTestParams{"../../maps/map6.ber", 1},
		HasExitTestParams{"../../maps/map7.ber", 1},
		HasExitTestParams{"../../maps/no_exit_path_1.ber", 0},
		HasExitTestParams{"../../maps/no_exit_path_2.ber", 0},
		HasExitTestParams{"../../maps/blocked_col.ber", 0},
		HasExitTestParams{"../../maps/blocked_exit.ber", 0}
	),
	[](const testing::TestParamInfo<HasExitTest::ParamType>& info) {
      std::string name = extractAndCleanFileName(info.param.path);
      return name;
    }
);

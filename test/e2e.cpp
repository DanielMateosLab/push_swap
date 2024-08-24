#include "gtest/gtest.h"
#include <string>
#include <array>
#include <cstdio>
#include <memory>

extern "C" {
#include "push_swap.h"
}

// Helper function to run a command and capture its output
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

class ExecutableBase {
	protected:
    std::string exec_path = "../../push_swap";

    std::string runExecutable(const std::string& args) {
        std::string command = exec_path + " " + args;
        return exec(command.c_str());
    }
};

class ExecutableTest : public ::testing::Test, public ExecutableBase {};

#define ASSERT_CONTAINS(haystack, needle) \
    EXPECT_NE(haystack.find(needle), std::string::npos) \
        << "Expected to find '" << needle << "' in:\n" << haystack


struct ParametersTestParams {
    const char* args;
    const char* expected_output;
};

class ParametersTest :
	public ExecutableBase,
	public ::testing::TestWithParam<ParametersTestParams>
{};

TEST_P(ParametersTest, Parameters) {
	const auto& params = GetParam();
	std::string output = runExecutable(params.args);
	ASSERT_CONTAINS(output, params.expected_output);
}

INSTANTIATE_TEST_SUITE_P(
	ParametersTests,
	ParametersTest,
	::testing::Values(
		ParametersTestParams{"", ""},
		ParametersTestParams{"arg1 arg2", ""},
		ParametersTestParams{"+9", ""},
		ParametersTestParams{"20 9!", "Error. Invalid number\n"},
		ParametersTestParams{"20 +9", "Error. Invalid number\n"},
		ParametersTestParams{"20 --9", "Error. Invalid number\n"},
		ParametersTestParams{"20 9-9", "Error. Invalid number\n"}
	)
);

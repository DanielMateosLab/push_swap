#include "gtest/gtest.h"
#include <string>
#include <array>
#include <cstdio>
#include <memory>

extern "C" {
#include "push_swap.h"
}

struct CommandOutput {
    std::string stdout;
    std::string stderr;
};

CommandOutput exec(const char* cmd) {
    std::array<char, 128> buffer;
    CommandOutput result;
    std::string command = std::string(cmd);

    // Capture stdout
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result.stdout += buffer.data();
    }

    // Capture stderr
    command += " 2>&1";
    std::unique_ptr<FILE, decltype(&pclose)> pipe_err(popen(command.c_str(), "r"), pclose);
    if (!pipe_err) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe_err.get()) != nullptr) {
        result.stderr += buffer.data();
    }

    return result;
}

class ExecutableBase {
protected:
    std::string exec_path = "../../push_swap";

    CommandOutput runExecutable(const std::string& args) {
        std::string command = exec_path + " " + args;
        return exec(command.c_str());
    }
};

class ExecutableTest : public ::testing::Test, public ExecutableBase {};

#define ASSERT_CONTAINS(haystack, needle) \
    EXPECT_NE(haystack.find(needle), std::string::npos) \
        << "Expected to find '" << needle << "' in:\n" << haystack

class ParametersTest : public ExecutableTest {
protected:
    void RunTest(const std::string& args,
                 const std::string& expected_stdout = "",
                 const std::string& expected_stderr = "",
                 bool accept_any_stdout = false,
                 bool accept_any_stderr = false) {
        CommandOutput output = runExecutable(args);

        if (accept_any_stdout) {
            // Accept any stdout
        } else if (expected_stdout.empty()) {
            EXPECT_TRUE(output.stdout.empty()) << "Expected empty stdout, but got: " << output.stdout;
        } else {
            ASSERT_CONTAINS(output.stdout, expected_stdout);
        }

        if (accept_any_stderr) {
            // Accept any stderr
        } else if (expected_stderr.empty()) {
            EXPECT_TRUE(output.stderr.empty()) << "Expected empty stderr, but got: " << output.stderr;
        } else {
            ASSERT_CONTAINS(output.stderr, expected_stderr);
        }
    }
};

TEST_F(ParametersTest, EmptyInput) {
    RunTest("", "", "");
}

TEST_F(ParametersTest, SinglePositiveNumber) {
    RunTest("+9", "", "");
}

TEST_F(ParametersTest, SingleNegativeNumber) {
    RunTest("-9", "", "");
}

TEST_F(ParametersTest, InvalidArgument) {
    RunTest("1 arg2", "", "Error\n");
}

TEST_F(ParametersTest, InvalidCharacter) {
    RunTest("20 9!", "", "Error\n");
}

TEST_F(ParametersTest, InvalidDoubleNegative) {
    RunTest("20 --9", "", "Error\n");
}

TEST_F(ParametersTest, InvalidNumberFormat) {
    RunTest("20 9-9", "", "Error\n");
}

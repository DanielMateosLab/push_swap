cmake_minimum_required(VERSION 3.5)

project(push_swap_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Set up GOOGLE TEST ###
configure_file(CMakeLists.txt.in
	googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
	${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
##

## Declare variables ##
set(PARENT_DIR ${PROJECT_SOURCE_DIR}/..)
set(LIBFT_DIR ${PARENT_DIR}/libs/libft)

# Include directories for tests ##
include_directories(
	"${PARENT_DIR}/include"
	"${LIBFT_DIR}/include"
)

## Set up e2e tests ##
# Register sources for the e2e executable so push_swap is recompiled after changes
file(GLOB_RECURSE PUSH_SWAP_SOURCES
    "${PARENT_DIR}/src/*.c"
    "${PARENT_DIR}/include/*.h"
    "${PARENT_DIR}/Makefile"
)
# Compile push swap (as a custom target) with dependencies
add_custom_target(push_swap ALL
    COMMAND make -C ${PARENT_DIR} -j${PROCESS_NUMBER}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${PUSH_SWAP_SOURCES}
)

## Add implementation code source for unit tests ##
file(GLOB sources
	"${PARENT_DIR}/src/*.c"
	"${PARENT_DIR}/include/*.h"
)
list(REMOVE_ITEM sources "${PARENT_DIR}/src/main.c")

## Add test files sources ##
file(GLOB tests "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.cpp")

# Compile libft
add_custom_target(libft
	COMMAND make -C ${LIBFT_DIR} -j${PROCESS_NUMBER}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Leaks test helper function (executes the test with leaks or valgrind)
function(add_leak_test test_name executable)
	if(APPLE)
		add_test(NAME ${test_name}_leaks
			COMMAND leaks -atExit -- $<TARGET_FILE:${executable}>)
	elseif(UNIX)
		find_program(VALGRIND "valgrind")
		if(VALGRIND)
			add_test(NAME ${test_name}_leaks
					COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 $<TARGET_FILE:${executable}>)
		endif()
	endif()
	set_tests_properties(${test_name}_leaks PROPERTIES DEPENDS ${test_name}) # If normal test fails, leaks test is skipped
endfunction()

# Add tests
foreach(file ${tests})
	set(name)
	get_filename_component(name ${file} NAME_WE)
	add_executable("${name}_tests"
		${sources}
		${file}
		"${PROJECT_SOURCE_DIR}/main.cpp")
	add_dependencies(${name}_tests libft push_swap)
	target_link_libraries(
		"${name}_tests" gtest_main
  		${LIBFT_DIR}/libft.a
	)
	add_test(NAME ${name} COMMAND "${name}_tests")
	# Add leak test if file name doesn't contain e2e
	if(NOT ${file} MATCHES "e2e")
		add_leak_test(${name} "${name}_tests")
	endif()
endforeach()

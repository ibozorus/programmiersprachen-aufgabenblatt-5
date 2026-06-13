# ---------------------------------------------------------------------------
# Test executable
#   file(GLOB_RECURSE ...) automatically collects all .test files in this
#   directory and its subdirectories. Each .test file contains TEST_CASE
#   definitions that are #included by tests.cpp. This way we can organize
#   tests into separate files without listing each one manually.
# ---------------------------------------------------------------------------
file(GLOB_RECURSE TEST_FILES *.test)

add_executable(tests
        tests.cpp
        list_iterator.hpp
        list_node.hpp
        list.hpp
        ${TEST_FILES}
        aufgabe_13.hpp
)

# Register the test executable with ctest
add_test(NAME doctest COMMAND tests)

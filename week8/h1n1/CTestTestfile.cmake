# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week8/h1n1
# Build directory: /Users/dianamin/Desktop/algo_lab2/week8/h1n1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week8/h1n1" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "h1n1_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week8/h1n1/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "h1n1_;main" LABELS "h1n1_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week8/h1n1/__exec_test_dir")
add_test(h1n1__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week8/h1n1" "/Users/dianamin/Desktop/algo_lab2/week8/h1n1/__exec_test_dir")
set_tests_properties(h1n1__SetupFixture PROPERTIES  FIXTURES_SETUP "h1n1_" LABELS "h1n1_")
add_test(h1n1__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week8/h1n1/__exec_test_dir")
set_tests_properties(h1n1__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "h1n1_" LABELS "h1n1_")

# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week7/maximum
# Build directory: /Users/dianamin/Desktop/algo_lab2/week7/maximum
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week7/maximum" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "maximum_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week7/maximum/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "maximum_;main" LABELS "maximum_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week7/maximum/__exec_test_dir")
add_test(maximum__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week7/maximum" "/Users/dianamin/Desktop/algo_lab2/week7/maximum/__exec_test_dir")
set_tests_properties(maximum__SetupFixture PROPERTIES  FIXTURES_SETUP "maximum_" LABELS "maximum_")
add_test(maximum__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week7/maximum/__exec_test_dir")
set_tests_properties(maximum__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "maximum_" LABELS "maximum_")

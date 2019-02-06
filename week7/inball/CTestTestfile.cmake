# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week7/inball
# Build directory: /Users/dianamin/Desktop/algo_lab2/week7/inball
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week7/inball" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "inball_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week7/inball/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "inball_;main" LABELS "inball_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week7/inball/__exec_test_dir")
add_test(inball__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week7/inball" "/Users/dianamin/Desktop/algo_lab2/week7/inball/__exec_test_dir")
set_tests_properties(inball__SetupFixture PROPERTIES  FIXTURES_SETUP "inball_" LABELS "inball_")
add_test(inball__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week7/inball/__exec_test_dir")
set_tests_properties(inball__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "inball_" LABELS "inball_")

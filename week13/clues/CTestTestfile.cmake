# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week13/clues
# Build directory: /Users/dianamin/Desktop/algo_lab2/week13/clues
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week13/clues" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "clues_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week13/clues/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "clues_;main" LABELS "clues_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week13/clues/__exec_test_dir")
add_test(clues__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week13/clues" "/Users/dianamin/Desktop/algo_lab2/week13/clues/__exec_test_dir")
set_tests_properties(clues__SetupFixture PROPERTIES  FIXTURES_SETUP "clues_" LABELS "clues_")
add_test(clues__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week13/clues/__exec_test_dir")
set_tests_properties(clues__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "clues_" LABELS "clues_")

# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week3/hit
# Build directory: /Users/dianamin/Desktop/algo_lab2/week3/hit
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week3/hit" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "hit_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week3/hit/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "hit_;main" LABELS "hit_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week3/hit/__exec_test_dir")
add_test(hit__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week3/hit" "/Users/dianamin/Desktop/algo_lab2/week3/hit/__exec_test_dir")
set_tests_properties(hit__SetupFixture PROPERTIES  FIXTURES_SETUP "hit_" LABELS "hit_")
add_test(hit__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week3/hit/__exec_test_dir")
set_tests_properties(hit__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "hit_" LABELS "hit_")

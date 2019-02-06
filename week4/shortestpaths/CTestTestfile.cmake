# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week4/shortestpaths
# Build directory: /Users/dianamin/Desktop/algo_lab2/week4/shortestpaths
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week4/shortestpaths" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "shortestpaths_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week4/shortestpaths/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "shortestpaths_;main" LABELS "shortestpaths_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week4/shortestpaths/__exec_test_dir")
add_test(shortestpaths__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week4/shortestpaths" "/Users/dianamin/Desktop/algo_lab2/week4/shortestpaths/__exec_test_dir")
set_tests_properties(shortestpaths__SetupFixture PROPERTIES  FIXTURES_SETUP "shortestpaths_" LABELS "shortestpaths_")
add_test(shortestpaths__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week4/shortestpaths/__exec_test_dir")
set_tests_properties(shortestpaths__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "shortestpaths_" LABELS "shortestpaths_")

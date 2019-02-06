# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week3/hiking-maps
# Build directory: /Users/dianamin/Desktop/algo_lab2/week3/hiking-maps
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week3/hiking-maps" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "hiking-maps_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week3/hiking-maps/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "hiking-maps_;main" LABELS "hiking-maps_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week3/hiking-maps/__exec_test_dir")
add_test(hiking-maps__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week3/hiking-maps" "/Users/dianamin/Desktop/algo_lab2/week3/hiking-maps/__exec_test_dir")
set_tests_properties(hiking-maps__SetupFixture PROPERTIES  FIXTURES_SETUP "hiking-maps_" LABELS "hiking-maps_")
add_test(hiking-maps__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week3/hiking-maps/__exec_test_dir")
set_tests_properties(hiking-maps__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "hiking-maps_" LABELS "hiking-maps_")

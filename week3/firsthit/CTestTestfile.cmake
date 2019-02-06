# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week3/firsthit
# Build directory: /Users/dianamin/Desktop/algo_lab2/week3/firsthit
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week3/firsthit" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "firsthit_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week3/firsthit/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "firsthit_;main" LABELS "firsthit_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week3/firsthit/__exec_test_dir")
add_test(firsthit__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week3/firsthit" "/Users/dianamin/Desktop/algo_lab2/week3/firsthit/__exec_test_dir")
set_tests_properties(firsthit__SetupFixture PROPERTIES  FIXTURES_SETUP "firsthit_" LABELS "firsthit_")
add_test(firsthit__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week3/firsthit/__exec_test_dir")
set_tests_properties(firsthit__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "firsthit_" LABELS "firsthit_")

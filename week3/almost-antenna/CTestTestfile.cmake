# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week3/almost-antenna
# Build directory: /Users/dianamin/Desktop/algo_lab2/week3/almost-antenna
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week3/almost-antenna" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "almost-antenna_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week3/almost-antenna/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "almost-antenna_;main" LABELS "almost-antenna_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week3/almost-antenna/__exec_test_dir")
add_test(almost-antenna__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week3/almost-antenna" "/Users/dianamin/Desktop/algo_lab2/week3/almost-antenna/__exec_test_dir")
set_tests_properties(almost-antenna__SetupFixture PROPERTIES  FIXTURES_SETUP "almost-antenna_" LABELS "almost-antenna_")
add_test(almost-antenna__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week3/almost-antenna/__exec_test_dir")
set_tests_properties(almost-antenna__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "almost-antenna_" LABELS "almost-antenna_")

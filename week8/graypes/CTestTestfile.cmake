# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week8/graypes
# Build directory: /Users/dianamin/Desktop/algo_lab2/week8/graypes
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week8/graypes" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "graypes_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week8/graypes/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "graypes_;main" LABELS "graypes_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week8/graypes/__exec_test_dir")
add_test(graypes__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week8/graypes" "/Users/dianamin/Desktop/algo_lab2/week8/graypes/__exec_test_dir")
set_tests_properties(graypes__SetupFixture PROPERTIES  FIXTURES_SETUP "graypes_" LABELS "graypes_")
add_test(graypes__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week8/graypes/__exec_test_dir")
set_tests_properties(graypes__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "graypes_" LABELS "graypes_")

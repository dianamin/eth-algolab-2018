# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week10/goldeneye
# Build directory: /Users/dianamin/Desktop/algo_lab2/week10/goldeneye
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week10/goldeneye" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "goldeneye_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week10/goldeneye/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "goldeneye_;main" LABELS "goldeneye_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week10/goldeneye/__exec_test_dir")
add_test(goldeneye__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week10/goldeneye" "/Users/dianamin/Desktop/algo_lab2/week10/goldeneye/__exec_test_dir")
set_tests_properties(goldeneye__SetupFixture PROPERTIES  FIXTURES_SETUP "goldeneye_" LABELS "goldeneye_")
add_test(goldeneye__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week10/goldeneye/__exec_test_dir")
set_tests_properties(goldeneye__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "goldeneye_" LABELS "goldeneye_")

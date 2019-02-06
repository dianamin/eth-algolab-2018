# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week12/hongkong
# Build directory: /Users/dianamin/Desktop/algo_lab2/week12/hongkong
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week12/hongkong" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "hongkong_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week12/hongkong/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "hongkong_;main" LABELS "hongkong_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week12/hongkong/__exec_test_dir")
add_test(hongkong__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week12/hongkong" "/Users/dianamin/Desktop/algo_lab2/week12/hongkong/__exec_test_dir")
set_tests_properties(hongkong__SetupFixture PROPERTIES  FIXTURES_SETUP "hongkong_" LABELS "hongkong_")
add_test(hongkong__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week12/hongkong/__exec_test_dir")
set_tests_properties(hongkong__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "hongkong_" LABELS "hongkong_")

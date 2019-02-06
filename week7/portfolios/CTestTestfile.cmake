# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week7/portfolios
# Build directory: /Users/dianamin/Desktop/algo_lab2/week7/portfolios
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week7/portfolios" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "portfolios_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week7/portfolios/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "portfolios_;main" LABELS "portfolios_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week7/portfolios/__exec_test_dir")
add_test(portfolios__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week7/portfolios" "/Users/dianamin/Desktop/algo_lab2/week7/portfolios/__exec_test_dir")
set_tests_properties(portfolios__SetupFixture PROPERTIES  FIXTURES_SETUP "portfolios_" LABELS "portfolios_")
add_test(portfolios__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week7/portfolios/__exec_test_dir")
set_tests_properties(portfolios__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "portfolios_" LABELS "portfolios_")

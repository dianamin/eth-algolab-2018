# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week12/radiation
# Build directory: /Users/dianamin/Desktop/algo_lab2/week12/radiation
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week12/radiation" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "radiation_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week12/radiation/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "radiation_;main" LABELS "radiation_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week12/radiation/__exec_test_dir")
add_test(radiation__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week12/radiation" "/Users/dianamin/Desktop/algo_lab2/week12/radiation/__exec_test_dir")
set_tests_properties(radiation__SetupFixture PROPERTIES  FIXTURES_SETUP "radiation_" LABELS "radiation_")
add_test(radiation__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week12/radiation/__exec_test_dir")
set_tests_properties(radiation__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "radiation_" LABELS "radiation_")

# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week7/worldcup
# Build directory: /Users/dianamin/Desktop/algo_lab2/week7/worldcup
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week7/worldcup" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "worldcup_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week7/worldcup/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "worldcup_;main" LABELS "worldcup_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week7/worldcup/__exec_test_dir")
add_test(worldcup__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week7/worldcup" "/Users/dianamin/Desktop/algo_lab2/week7/worldcup/__exec_test_dir")
set_tests_properties(worldcup__SetupFixture PROPERTIES  FIXTURES_SETUP "worldcup_" LABELS "worldcup_")
add_test(worldcup__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week7/worldcup/__exec_test_dir")
set_tests_properties(worldcup__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "worldcup_" LABELS "worldcup_")

# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week7/suez
# Build directory: /Users/dianamin/Desktop/algo_lab2/week7/suez
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week7/suez" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "suez_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week7/suez/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "suez_;main" LABELS "suez_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week7/suez/__exec_test_dir")
add_test(suez__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week7/suez" "/Users/dianamin/Desktop/algo_lab2/week7/suez/__exec_test_dir")
set_tests_properties(suez__SetupFixture PROPERTIES  FIXTURES_SETUP "suez_" LABELS "suez_")
add_test(suez__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week7/suez/__exec_test_dir")
set_tests_properties(suez__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "suez_" LABELS "suez_")

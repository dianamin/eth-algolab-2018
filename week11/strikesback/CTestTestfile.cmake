# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week11/strikesback
# Build directory: /Users/dianamin/Desktop/algo_lab2/week11/strikesback
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week11/strikesback" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "strikesback_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week11/strikesback/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "strikesback_;main" LABELS "strikesback_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week11/strikesback/__exec_test_dir")
add_test(strikesback__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week11/strikesback" "/Users/dianamin/Desktop/algo_lab2/week11/strikesback/__exec_test_dir")
set_tests_properties(strikesback__SetupFixture PROPERTIES  FIXTURES_SETUP "strikesback_" LABELS "strikesback_")
add_test(strikesback__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week11/strikesback/__exec_test_dir")
set_tests_properties(strikesback__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "strikesback_" LABELS "strikesback_")

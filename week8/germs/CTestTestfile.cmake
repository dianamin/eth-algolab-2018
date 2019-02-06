# CMake generated Testfile for 
# Source directory: /Users/dianamin/Desktop/algo_lab2/week8/germs
# Build directory: /Users/dianamin/Desktop/algo_lab2/week8/germs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compilation_of__main "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "--build" "/Users/dianamin/Desktop/algo_lab2/week8/germs" "--target" "main")
set_tests_properties(compilation_of__main PROPERTIES  FIXTURES_SETUP "main" LABELS "germs_")
add_test(execution___of__main "/Users/dianamin/Desktop/algo_lab2/week8/germs/main")
set_tests_properties(execution___of__main PROPERTIES  DEPENDS "compilation_of__main" FIXTURES_REQUIRED "germs_;main" LABELS "germs_" WORKING_DIRECTORY "/Users/dianamin/Desktop/algo_lab2/week8/germs/__exec_test_dir")
add_test(germs__SetupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "copy_directory" "/Users/dianamin/Desktop/algo_lab2/week8/germs" "/Users/dianamin/Desktop/algo_lab2/week8/germs/__exec_test_dir")
set_tests_properties(germs__SetupFixture PROPERTIES  FIXTURES_SETUP "germs_" LABELS "germs_")
add_test(germs__CleanupFixture "/usr/local/Cellar/cmake/3.12.3/bin/cmake" "-E" "remove_directory" "/Users/dianamin/Desktop/algo_lab2/week8/germs/__exec_test_dir")
set_tests_properties(germs__CleanupFixture PROPERTIES  FIXTURES_CLEANUP "germs_" LABELS "germs_")

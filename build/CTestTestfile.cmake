# CMake generated Testfile for 
# Source directory: /home/user/Documents/jqr-calcprojects
# Build directory: /home/user/Documents/jqr-calcprojects/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestSimpleCalc "bash" "/home/user/Documents/jqr-calcprojects/local_tester.sh" "1_SimpleCalc")
set_tests_properties(TestSimpleCalc PROPERTIES  WORKING_DIRECTORY "/home/user/Documents/jqr-calcprojects" _BACKTRACE_TRIPLES "/home/user/Documents/jqr-calcprojects/CMakeLists.txt;34;add_test;/home/user/Documents/jqr-calcprojects/CMakeLists.txt;0;")
add_test(TestFileCalc "bash" "/home/user/Documents/jqr-calcprojects/local_tester.sh" "2_FileCalc")
set_tests_properties(TestFileCalc PROPERTIES  WORKING_DIRECTORY "/home/user/Documents/jqr-calcprojects" _BACKTRACE_TRIPLES "/home/user/Documents/jqr-calcprojects/CMakeLists.txt;40;add_test;/home/user/Documents/jqr-calcprojects/CMakeLists.txt;0;")
add_test(TestDataStructures1 "bash" "/home/user/Documents/jqr-calcprojects/local_tester.sh" "3_DataStructures1")
set_tests_properties(TestDataStructures1 PROPERTIES  WORKING_DIRECTORY "/home/user/Documents/jqr-calcprojects" _BACKTRACE_TRIPLES "/home/user/Documents/jqr-calcprojects/CMakeLists.txt;46;add_test;/home/user/Documents/jqr-calcprojects/CMakeLists.txt;0;")
add_test(TestThreadCalc "bash" "/home/user/Documents/jqr-calcprojects/local_tester.sh" "4_ThreadCalc")
set_tests_properties(TestThreadCalc PROPERTIES  WORKING_DIRECTORY "/home/user/Documents/jqr-calcprojects" _BACKTRACE_TRIPLES "/home/user/Documents/jqr-calcprojects/CMakeLists.txt;52;add_test;/home/user/Documents/jqr-calcprojects/CMakeLists.txt;0;")
add_test(TestNetCalc "bash" "/home/user/Documents/jqr-calcprojects/local_tester.sh" "5_NetCalc")
set_tests_properties(TestNetCalc PROPERTIES  WORKING_DIRECTORY "/home/user/Documents/jqr-calcprojects" _BACKTRACE_TRIPLES "/home/user/Documents/jqr-calcprojects/CMakeLists.txt;58;add_test;/home/user/Documents/jqr-calcprojects/CMakeLists.txt;0;")
subdirs("1_SimpleCalc")

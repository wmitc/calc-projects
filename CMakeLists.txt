cmake_minimum_required(VERSION 3.16)

enable_testing()

project(
    JQRCalcProjects
    LANGUAGES "C"
    DESCRIPTION "JQR Example Projects v1.5"
)

include(jqr_main.cmake)


if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/0_Common/CMakeLists.txt")
    add_subdirectory(0_Common)
endif()

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/1_SimpleCalc/CMakeLists.txt")
    add_subdirectory(1_SimpleCalc)
endif()

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/2_FileCalc/CMakeLists.txt")
    add_subdirectory(2_FileCalc)
endif()

# if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/4_ThreadCalc/CMakeLists.txt")
#     add_subdirectory(4_ThreadCalc)
# endif()

# if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/5_NetCalc/CMakeLists.txt")
#     add_subdirectory(5_NetCalc)
# endif()

add_test(
    NAME TestSimpleCalc
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND bash ${CMAKE_SOURCE_DIR}/local_tester.sh 1_SimpleCalc
)

add_test(
    NAME TestFileCalc
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND bash ${CMAKE_SOURCE_DIR}/local_tester.sh 2_FileCalc
)

add_test(
    NAME TestDataStructures1
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND bash ${CMAKE_SOURCE_DIR}/local_tester.sh 3_DataStructures1
)

add_test(
    NAME TestThreadCalc
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND bash ${CMAKE_SOURCE_DIR}/local_tester.sh 4_ThreadCalc
)

add_test(
    NAME TestNetCalc
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND bash ${CMAKE_SOURCE_DIR}/local_tester.sh 5_NetCalc
)

# EOF

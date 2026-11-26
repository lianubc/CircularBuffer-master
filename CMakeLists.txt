cmake_minimum_required(VERSION 3.11.0)
project(stack VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare( 
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(CIRCULAR_BUFFER_LIB_SOURCES CircularBufferLib/CircularBuffer.h CircularBufferLib/CircularBuffer.cpp)
set(CIRCULAR_BUFFER_APP_SOURCES CircularBufferApp/CircularBufferApp.cpp)
set(CIRCULAR_BUFFER_TESTS_SOURCES CircularBufferUnitTest/CircularBufferUnitTest.cpp)

enable_testing()
add_executable(CircularBufferApp ${CIRCULAR_BUFFER_APP_SOURCES} ${CIRCULAR_BUFFER_LIB_SOURCES} )
add_executable(CircularBufferTests ${CIRCULAR_BUFFER_TESTS_SOURCES} ${CIRCULAR_BUFFER_LIB_SOURCES})
target_link_libraries(CircularBufferTests GTest::gtest_main)

include(CTest)
include(GoogleTest)
gtest_discover_tests(CircularBufferTests)
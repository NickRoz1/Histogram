cmake_minimum_required(VERSION 3.10)


project(Histogram VERSION 1.0)

find_package(PythonLibs REQUIRED)

set (CMAKE_CXX_FLAGS "-lstdc++fs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" 
                    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
                    ${PYTHON_INCLUDE_DIRS}) 

                    
set(SOURCE_FILES src/main.cpp src/hist.cpp 
                        tests/test.cpp src/hist.hpp 
                        tests/test.hpp src/gauss.cpp 
                        src/gauss.hpp)
                        
add_executable(Histogram ${SOURCE_FILES})



target_link_libraries(${PROJECT_NAME} stdc++fs ${PYTHON_LIBRARIES})

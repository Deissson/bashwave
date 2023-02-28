cmake_minimum_required(VERSION 3.16)
project(bashwave VERSION 1.0 DESCRIPTION "yet another set of tools")
 
add_subdirectory(lib/fmt)
	 
add_executable(${PROJECT_NAME}
    src/main.cpp
)
 
target_link_libraries(${PROJECT_NAME}
    fmt
)
 
target_include_directories(${PROJECT_NAME} PRIVATE
    lib/fmt/include
    include
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20 
    CXX_STANDARD_REQUIRED ON
)

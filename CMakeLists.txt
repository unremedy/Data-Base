cmake_minimum_required(VERSION 3.19)
project(DataBase)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        sources/BasicFaculty.cpp
        sources/BasicFacultyFunctions.cpp
        sources/GybridFacultyFunctions.cpp
        sources/IndustryFacultyFunctions.cpp
        sources/IndustryFaculty.cpp
        )

add_executable(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )

target_link_libraries(demo ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} demo
        EXPORT "${PROJECT_NAME}-targets"
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
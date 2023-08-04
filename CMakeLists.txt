cmake_minimum_required(VERSION 3.26)
set(project_name tabula)
project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/dto/DTOs.hpp
        src/controller/BoardController.hpp)

set_target_properties(${project_name}-lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${project_name}-lib PUBLIC src)

find_package(oatpp 1.3.0 REQUIRED)
target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
)

add_executable(${project_name}-exe
        src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

cmake_minimum_required(VERSION 3.26)
set(project_name tabula)
project(${project_name})

set(CMAKE_CXX_STANDARD 17)

# config library
add_library(${project_name}-config
        src/dto/configDto.hpp
)
set_target_properties(${project_name}-config PROPERTIES LINKER_LANGUAGE CXX)

# db library
add_library(${project_name}-db-lib
        src/db/TabulaColumnsClient.hpp
)
set_target_properties(${project_name}-db-lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${project_name}-db-lib PUBLIC src)

# main library
add_library(${project_name}-lib
        src/AppComponent.hpp
        src/dto/DTOs.hpp
        src/controller/BoardController.hpp
)
set_target_properties(${project_name}-lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${project_name}-lib PUBLIC src)

# test library
add_library(${project_name}-test-lib
        test/app/TestComponent.hpp
        test/app/TabulaApiTestClient.hpp
        test/BoardControllerTest.hpp
        test/BoardControllerTest.cpp)
set_target_properties(${project_name}-test-lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${project_name}-test-lib PUBLIC src)


# link oatpp packages
find_package(oatpp              1.3.0   REQUIRED)
find_package(oatpp-postgresql   1.3.0   REQUIRED)


target_link_libraries(${project_name}-db-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-postgresql
)
target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-postgresql
)
target_link_libraries(${project_name}-test-lib
        PUBLIC oatpp::oatpp-postgresql
        PUBLIC oatpp::oatpp-test
)

# add definitions
add_definitions(
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
        -DCONFIG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/config.json"
)

# add executables
add_executable(${project_name}-exe
        src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-config)
target_link_libraries(${project_name}-exe ${project_name}-db-lib)
target_link_libraries(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-tests
        test/Tests.cpp)
target_link_libraries(${project_name}-exe ${project_name}-config)
target_link_libraries(${project_name}-tests ${project_name}-db-lib)
target_link_libraries(${project_name}-tests ${project_name}-lib)
target_link_libraries(${project_name}-tests ${project_name}-test-lib)
add_test(NAME Tests COMMAND Tests)

add_executable(${project_name}-migrate
        src/Migrate.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-config)
target_link_libraries(${project_name}-migrate ${project_name}-db-lib)

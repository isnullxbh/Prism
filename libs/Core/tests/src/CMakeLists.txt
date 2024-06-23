find_package(GTest CONFIG REQUIRED)

add_executable(Prism.Core.Tests)

target_sources(Prism.Core.Tests
    PRIVATE
        main.cpp
        Matching/MatchClasses.cpp)

target_link_libraries(Prism.Core.Tests
    PRIVATE
        GTest::gtest
        Prism::Core)

add_custom_command(TARGET Prism.Core.Tests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../sources
        ${CMAKE_CURRENT_BINARY_DIR}/sources)

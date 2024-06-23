find_package(Clang CONFIG REQUIRED)

add_library(Prism.Core)

set_target_properties(Prism.Core
    PROPERTIES
        OUTPUT_NAME "Prism.Core"
        PREFIX      "")

target_include_directories(Prism.Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CLANG_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Prism.Core
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Entities/Class.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Extractors/DefaultExtractor.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/MatchCallbacks/ClassMatchCallback.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Entity.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/EntityBase.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/EntitySet.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Extractor.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/MatchCallback.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/MatchCallbackBase.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/MatcherSet.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/MatcherSetBuilder.hpp)

target_sources(Prism.Core
    PRIVATE
        Prism/Entities/Class.cpp
        Prism/Extractors/DefaultExtractor.cpp
        Prism/MatchCallbacks/ClassMatchCallback.cpp
        Prism/EntityBase.cpp
        Prism/EntitySet.cpp
        Prism/Extractor.cpp
        Prism/MatcherSet.cpp
        Prism/MatcherSetBuilder.cpp)

target_link_libraries(Prism.Core
    PUBLIC
        clangASTMatchers
        clangFrontend
        clangSerialization)

add_library(Prism::Core ALIAS Prism.Core)

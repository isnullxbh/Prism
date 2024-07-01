find_package(Clang CONFIG REQUIRED)

add_library(Prism)

set_target_properties(Prism
    PROPERTIES
        OUTPUT_NAME "Prism"
        PREFIX      "")

target_include_directories(Prism
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CLANG_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Prism
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Attributes/Annotation.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/ClassMembers/DataMember.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Entities/Class.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Extractors/MatcherBasedExtractor.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Utility/Slice.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Attribute.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/AttributeFactory.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/AttributeHolder.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/BaseTypes.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/ClassMember.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Declaration.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/DefaultAttributeHolder.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Entity.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/EntityBase.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/EntityFactory.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/EntitySet.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Extractor.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/MatchCallback.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Prism/Matchers.hpp)

target_sources(Prism
    PRIVATE
        Prism/Attributes/Annotation.cpp
        Prism/ClassMembers/DataMember.cpp
        Prism/Entities/Class.cpp
        Prism/Extractors/MatcherBasedExtractor.cpp
        Prism/AttributeFactory.cpp
        Prism/BaseTypes.cpp
        Prism/DefaultAttributeHolder.cpp
        Prism/Entity.cpp
        Prism/EntityBase.cpp
        Prism/EntityFactory.cpp
        Prism/EntitySet.cpp
        Prism/Extractor.cpp)

target_link_libraries(Prism
    PUBLIC
        clangASTMatchers
        clangFrontend
        clangSerialization)

add_library(Prism::Core ALIAS Prism)

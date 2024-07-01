/**
 * @file    ClassTests.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#include <filesystem>

#include <gtest/gtest.h>

#include <Prism/Extractors/MatcherBasedExtractor.hpp>
#include <Prism/Matchers.hpp>
#include <Prism/Entities/Class.hpp>
#include <Prism/Attributes/Annotation.hpp>

static const std::filesystem::path source_dir { "./sources" };

TEST(ClassTests, DataMembers)
{
    using namespace Prism;
    using Attributes::Annotation;

    MatcherBasedExtractor extractor {};
    extractor.addMatcher<clang::CXXRecordDecl>(class_matcher);
    const auto entity_set = extractor.extract(source_dir / "Classes" / "Members.hpp");

    const auto* c = entity_set.getEntityWithQualifiedName<Class>("Class");
    ASSERT_NE(c, nullptr);

    EXPECT_EQ(c->dataMembers().size(), 2U);

    EXPECT_EQ(c->dataMembers()[0].name(), "m1");
    EXPECT_EQ(c->dataMembers()[0].type(), "int");
    EXPECT_EQ(c->dataMembers()[0].accessibility(), Accessibility::Public);
    EXPECT_TRUE(c->dataMembers()[0].attributes().contains<Annotation>(
        Attributes::Predicates::annotationWithText("Field1")));

    EXPECT_EQ(c->dataMembers()[1].name(), "m3");
    EXPECT_EQ(c->dataMembers()[1].type(), "N1::T2");
    EXPECT_EQ(c->dataMembers()[1].accessibility(), Accessibility::Private);
    EXPECT_TRUE(c->dataMembers()[1].attributes().contains<Annotation>(
        Attributes::Predicates::annotationWithText("Field3")));
}

/**
 * @file    MatchClasses.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <filesystem>

#include <gtest/gtest.h>

#include <Prism/Extractors/DefaultExtractor.hpp>
#include <Prism/MatcherSetBuilder.hpp>
#include <Prism/Entities/Class.hpp>

static const std::filesystem::path source_dir { "./sources" };

TEST(MatchClasses, SkipForwardDeclarations)
{
    using namespace Prism;

    auto matchers =
        MatcherSetBuilder()
            .addClassMatcher()
            .build();

    DefaultExtractor extractor { std::move(matchers) };
    const auto entity_set = extractor.extract(source_dir / "Classes" / "ForwardDeclaration.hpp");

    EXPECT_EQ(entity_set.size(), 1U);
    EXPECT_TRUE(entity_set.hasEntityWithQualifiedName<Class>("A"));
}

TEST(MatchClasses, SkipClassTemplates)
{
    using namespace Prism;

    auto matchers =
        MatcherSetBuilder()
            .addClassMatcher()
            .build();

    DefaultExtractor extractor { std::move(matchers) };
    const auto entity_set = extractor.extract(source_dir / "Classes" / "Templates.hpp");

    EXPECT_EQ(entity_set.size(), 1U);
    EXPECT_TRUE(entity_set.hasEntityWithQualifiedName<Class>("A1"));
}

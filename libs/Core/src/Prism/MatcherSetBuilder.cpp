/**
 * @file    MatcherSetBuilder.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <Prism/MatcherSetBuilder.hpp>

#include <utility>

#include <clang/ASTMatchers/ASTMatchers.h>

#include <Prism/MatchCallbacks/ClassMatchCallback.hpp>

namespace Prism
{

auto MatcherSetBuilder::addClassMatcher()-> MatcherSetBuilder&
{
    using namespace clang::ast_matchers;
    constexpr std::string_view id { "c1" };

    auto matcher =
        cxxRecordDecl(
            unless(hasParent(classTemplateDecl())),     // Skip primary class template
            unless(isExplicitTemplateSpecialization()), // Skip class template specializations
            isDefinition())                             // Skip forward declarations
        .bind(id);

    _matchers.add(std::move(matcher), std::make_unique<ClassMatchCallback>(id));
    return *this;
}

auto MatcherSetBuilder::build()-> MatcherSet
{
    return std::exchange(_matchers, MatcherSet());
}

} // namespace Prism

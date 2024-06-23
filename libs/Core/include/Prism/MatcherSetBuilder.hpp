/**
 * @file    MatcherSetBuilder.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#pragma once

#include <Prism/MatcherSet.hpp>

namespace Prism
{

class MatcherSetBuilder
{
public:
    auto addClassMatcher() -> MatcherSetBuilder&;
    auto build() -> MatcherSet;

private:
    MatcherSet _matchers {};
};

} // namespace Prism

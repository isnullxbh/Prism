/**
 * @file    MatcherSet.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <Prism/MatcherSet.hpp>

namespace Prism
{

auto MatcherSet::add(DeclarationMatcher matcher, std::unique_ptr<MatchCallback> callback)-> void
{
    _entries.emplace_back(std::move(matcher), std::move(callback));
}

} // namespace Prism

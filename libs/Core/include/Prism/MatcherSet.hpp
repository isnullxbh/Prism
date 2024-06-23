/**
 * @file    MatcherSet.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#pragma once

#include <memory>
#include <vector>

#include <clang/ASTMatchers/ASTMatchers.h>

#include <Prism/MatchCallback.hpp>

namespace Prism
{

class MatcherSet
{
public:
    using DeclarationMatcher = clang::ast_matchers::DeclarationMatcher;

    auto add(DeclarationMatcher matcher, std::unique_ptr<MatchCallback> callback) -> void;

    template<typename F>
    auto for_each(F&& f) -> void
        requires std::is_invocable_v<F, DeclarationMatcher&, MatchCallback&>;

private:
    struct Entry
    {
        DeclarationMatcher             matcher;
        std::unique_ptr<MatchCallback> callback;
    };

    std::vector<Entry> _entries {};
};

template<typename F>
auto MatcherSet::for_each(F&& f) -> void
    requires std::is_invocable_v<F, DeclarationMatcher&, MatchCallback&>
{
    for (auto& [matcher, callbackPtr] : _entries)
    {
        f(matcher, *callbackPtr);
    }
}

} // namespace Prism

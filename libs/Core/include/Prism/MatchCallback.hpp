/**
 * @file    MatchCallback.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#pragma once

#include <string>
#include <string_view>

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace Prism
{

template<typename Declaration>
class MatchCallback
    : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
    explicit MatchCallback(std::string_view id);

    auto run(const clang::ast_matchers::MatchFinder::MatchResult& result) -> void override;

private:
    virtual auto consume(const Declaration* declaration) -> void = 0;

    std::string _id;
};

template<typename Declaration>
MatchCallback<Declaration>::MatchCallback(std::string_view id)
    : _id(id)
{
}

template<typename Declaration>
auto MatchCallback<Declaration>::run(const clang::ast_matchers::MatchFinder::MatchResult& result) -> void
{
    if (const auto declaration = result.Nodes.getNodeAs<Declaration>(_id))
    {
        consume(declaration);
    }
}

} // namespace Prism

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

/// A base class for match callbacks.
/// @tparam  Declaration Declaration type of matching entity.
/// @ingroup PrismCore
/// @since   0.1.0
template<typename Declaration>
class MatchCallback
    : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
    /// Constructs callback with the specified ID.
    /// ID is an unique identifier to which a specific matcher is associated.
    /// @param id Unique identifier.
    explicit MatchCallback(std::string_view id);

    auto run(const clang::ast_matchers::MatchFinder::MatchResult& result) -> void override;

private:
    /// A function that will be called when there is a match.
    /// @param declaration Declaration of the matching entity.
    virtual auto consume(const Declaration* declaration) -> void = 0;

    std::string _id; ///< ID.
};

template<typename Declaration>
MatchCallback<Declaration>::MatchCallback(std::string_view id)
    : _id(id)
{}

template<typename Declaration>
auto MatchCallback<Declaration>::run(const clang::ast_matchers::MatchFinder::MatchResult& result) -> void
{
    if (const auto declaration = result.Nodes.getNodeAs<Declaration>(_id))
    {
        consume(declaration);
    }
}

} // namespace Prism

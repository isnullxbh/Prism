/**
 * @file    MatchCallback.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#pragma once

#include <Prism/EntitySet.hpp>

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace Prism
{

class MatchCallback
    : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
    auto entitySet() const noexcept -> EntitySet*;
    auto setEntitySet(EntitySet& entities) -> void;

private:
    EntitySet* _entities {};
};

inline auto MatchCallback::entitySet() const noexcept-> EntitySet*
{
    return _entities;
}

inline auto MatchCallback::setEntitySet(EntitySet& entities)-> void
{
    _entities = &entities;
}

} // namespace Prism

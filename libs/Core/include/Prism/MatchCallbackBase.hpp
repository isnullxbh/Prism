/**
 * @file    MatchCallbackBase.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#pragma once

#include <string_view>
#include <string>
#include <type_traits>

#include <clang/AST/Decl.h>

#include <Prism/MatchCallback.hpp>

namespace Prism
{

template<typename Declaration>
    requires std::is_base_of_v<clang::NamedDecl, Declaration>
class MatchCallbackBase : public MatchCallback
{
public:
    explicit MatchCallbackBase(std::string_view id);

    auto id() const noexcept -> const std::string&;

private:
    std::string _id;
    EntitySet*  _entities {};
};

template<typename Declaration>
    requires std::is_base_of_v<clang::NamedDecl, Declaration>
MatchCallbackBase<Declaration>::MatchCallbackBase(std::string_view id)
    : _id(id)
{}

template<typename Declaration>
    requires std::is_base_of_v<clang::NamedDecl, Declaration>
auto MatchCallbackBase<Declaration>::id() const noexcept-> const std::string&
{
    return _id;
}

} // namespace Prism

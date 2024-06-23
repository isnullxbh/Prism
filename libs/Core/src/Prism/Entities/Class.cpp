/**
 * @file    Class.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <Prism/Entities/Class.hpp>

namespace Prism
{

Class::Class(const clang::CXXRecordDecl* declaration)
    : EntityBase(declaration)
{
}

auto Class::kind() const noexcept-> EntityKind
{
    return EntityKind::Class;
}

auto Class::clone() const noexcept-> Class*
{
    return new Class(*this);
}

} // namespace Prism

/**
 * @file    Class.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <Prism/Entities/Class.hpp>

namespace Prism
{

Class::Class(const clang::CXXRecordDecl* declaration, AttributeFactory& attribute_factory)
    : EntityBase(declaration, attribute_factory)
{
    extractDataMembers(declaration, attribute_factory, _data_members);
}

auto Class::kind() const noexcept-> EntityKind
{
    return EntityKind::Class;
}

auto Class::clone() const noexcept-> Class*
{
    return new Class(*this);
}

auto Class::dataMembers() const noexcept-> const DataMembers&
{
    return _data_members;
}

auto Class::extractDataMembers(const clang::CXXRecordDecl* declaration, AttributeFactory& factory, DataMembers& members)-> void
{
    for (auto it = declaration->field_begin(); it != declaration->field_end(); ++it)
    {
        members.emplace_back(*it, std::ref(factory));
    }
}

} // namespace Prism

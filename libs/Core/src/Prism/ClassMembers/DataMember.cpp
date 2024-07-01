/**
 * @file    DataMember.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#include <Prism/ClassMembers/DataMember.hpp>

namespace Prism
{

DataMember::DataMember(const clang::FieldDecl* declaration, AttributeFactory& attribute_factory)
    : _name(declaration->getNameAsString())
    , _type(declaration->getType().getAsString())
    , _accessibility(convertToAccessibility(declaration->getAccess()))
    , _attribute_holder(declaration, attribute_factory)
{}

auto DataMember::attributes() const noexcept -> const AttributeHolder&
{
    return _attribute_holder;
}

auto DataMember::name() const noexcept-> const std::string&
{
    return _name;
}

auto DataMember::type() const noexcept-> const std::string&
{
    return _type;
}

auto DataMember::accessibility() const noexcept-> Accessibility
{
    return _accessibility;
}

} // namespace Prism

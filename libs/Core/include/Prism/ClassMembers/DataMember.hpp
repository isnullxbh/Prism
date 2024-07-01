/**
 * @file    DataMember.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

#include <clang/AST/DeclCXX.h>

#include <Prism/ClassMember.hpp>
#include <Prism/DefaultAttributeHolder.hpp>

namespace Prism
{

/// Class data member.
/// @ingroup PrismCore
/// @since   0.1.0
class DataMember : public ClassMember
{
public:
    /// Constructs data member from the specified declaration.
    /// @param declaration       Data member declaration.
    /// @param attribute_factory Attribute factory.
    explicit DataMember(const clang::FieldDecl* declaration, AttributeFactory& attribute_factory);

    auto attributes() const noexcept -> const AttributeHolder& final;
    constexpr auto kind() const noexcept -> Kind final { return Kind::DataMember; }
    auto name() const noexcept -> const std::string& final;
    auto type() const noexcept -> const std::string& final;
    auto accessibility() const noexcept -> Accessibility final;

private:
    std::string            _name;             ///< Name.
    std::string            _type;             ///< Type in human-readable representation.
    Accessibility          _accessibility;    ///< Access specifier.
    DefaultAttributeHolder _attribute_holder; ///< Attributes.
};

} // namespace Prism

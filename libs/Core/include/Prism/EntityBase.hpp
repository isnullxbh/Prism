/**
 * @file    EntityBase.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <Prism/Entity.hpp>
#include <Prism/AttributeFactory.hpp>
#include <Prism/DefaultAttributeHolder.hpp>

namespace clang { class NamedDecl; }

namespace Prism
{

/// Implements the part of the Entity interface which is same for all entities.
/// @ingroup PrismCore
/// @since   0.1.0
class EntityBase : public Entity
{
public:
    auto attributes() const noexcept -> const AttributeHolder& final;
    auto name() const noexcept -> const std::string& final;
    auto qualifiedName() const noexcept -> const std::string& final;
    auto location() const noexcept -> const std::filesystem::path& final;

protected:
    /// Constructor.
    /// Retrieves attributes applied to the entity.
    /// @param declaration       Entity declaration.
    /// @param attribute_factory Attribute factory.
    explicit EntityBase(const clang::NamedDecl* declaration, AttributeFactory& attribute_factory);

private:
    std::string            _name;               ///< Name.
    std::string            _qualified_name;     ///< Qualified name.
    std::filesystem::path  _location;           ///< Location.
    DefaultAttributeHolder _attributes_holder;  ///< Attributes.
};

} // namespace Prism

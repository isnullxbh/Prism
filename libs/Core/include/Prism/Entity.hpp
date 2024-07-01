/**
 * @file    Entity.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <filesystem>
#include <string>
#include <string_view>

#include <Prism/Declaration.hpp>

namespace Prism
{

/// Defines entity kinds.
/// @ingroup PrismCore
/// @since   0.1.0
enum class EntityKind
{
    Class,              ///< Indicates that entity is a class.
    ClassTemplate,      ///< Indicates that entity is a class template.
    Enumeration,        ///< Indicates that entity is an enumeration.
    Function,           ///< Indicates that entity is a function.
    FunctionTemplate,   ///< Indicates that entity is a function template.
    TypeAlias,          ///< Indicates that entity is a type alias.
    TypeAliasTemplate,  ///< Indicates that entity is a type alias template.
};

/// A base class for C++ entities.
/// @ingroup PrismCore
/// @since   0.1.0
class Entity : public Declaration
{
public:
    /// Gets the kind of the entity.
    /// @return Kind.
    virtual auto kind() const noexcept -> EntityKind = 0;

    /// Gets the name of the entity.
    /// @return A string that contains entity name.
    virtual auto name() const noexcept -> const std::string& = 0;

    /// Gets the qualified name of the entity.
    /// @return A string that contains entityt qualified name.
    virtual auto qualifiedName() const noexcept -> const std::string& = 0;

    /// Creates a copy of the entity.
    /// @return A pointer to the created entity object.
    virtual auto clone() const noexcept -> Entity* = 0;

    /// Gets the location where the entity is defined.
    /// @return A path to source file with entity definition.
    virtual auto location() const noexcept -> const std::filesystem::path& = 0;
};

/// Defines entity traits.
/// @tparam  ConcreteEntity Entity type.
/// @ingroup PrismCore
/// @since   0.1.0
template<typename ConcreteEntity>
struct EntityTraits;

namespace Predicates
{

/// Builds a predicate to search entity by it's qualified name.
constexpr inline auto byQualifiedName = [](std::string_view qualifiedName)
{
    return [=](const Entity& entity){ return entity.qualifiedName() == qualifiedName; };
};

} // namespace Predicates
} // namespace Prism

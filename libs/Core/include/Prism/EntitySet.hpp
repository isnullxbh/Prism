/**
 * @file    EntitySet.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <type_traits>
#include <unordered_map>
#include <vector>
#include <memory>

#include <Prism/Entity.hpp>

namespace Prism
{

/// An entity set.
/// @ingroup PrismCore
/// @since   0.1.0
/// @todo    Make find methods public, make changes to other methods according to this.
class EntitySet
{
private:
    /// A type of entity list.
    using EntityList = std::vector<std::unique_ptr<Entity>>;
    /// A type of associative container that maps entity kind to list of entities of that kind.
    using EntityListPerKind = std::unordered_map<EntityKind, EntityList>;

public:
    /// Checks whether the set is empty.
    /// @return If the set is empty - true, otherwise - false.
    auto empty() const noexcept -> bool;

    /// Gets the number of entities in the set.
    /// @return Number of entities.
    auto size() const noexcept -> std::size_t;

    /// Checks if set contains entity with the specified qualified name.
    /// @param  qualifiedName Entity qualified name.
    /// @return If the set contains entity with the specified qualified name - true, otherwise - false.
    auto hasEntityWithQualifiedName(std::string_view qualifiedName) const noexcept -> bool;

    /// Checks if the set contains entity of the specified type and qualified name.
    /// @tparam ConcreteEntity Entity type.
    /// @param  name           Entity qualified name.
    /// @return If the set contains entity that meets the specified criteria - true, otherwise - false.
    template<typename ConcreteEntity>
        requires std::is_base_of_v<Entity, ConcreteEntity>
    auto hasEntityWithQualifiedName(std::string_view name) const noexcept -> bool;

    /// Adds the specified entity to the set.
    /// @param entity Entity to add.
    auto addEntity(std::unique_ptr<Entity> entity) -> void;

    /// Gets the entity of the specified type and qualified name.
    /// @tparam ConcreteEntity Entity type.
    /// @param  name           Entity qualified name.
    /// @return If the set contains entity that meets the specified criteria - a pointer to the entity,
    ///         otherwise - null pointer.
    template<typename ConcreteEntity>
        requires std::is_base_of_v<Entity, ConcreteEntity>
    auto getEntityWithQualifiedName(std::string_view name) const noexcept -> const ConcreteEntity*;

private:
    /// Finds entity that meets the specified predicate.
    /// @tparam Predicate Predicate type.
    /// @param  predicate Predicate.
    /// @return If the set contains entity that meets the specified criteria - a pointer to the entity,
    ///         otherwise - nullptr.
    template<typename Predicate>
        requires std::is_invocable_r_v<bool, Predicate, const Entity&>
    auto findBy(Predicate&& predicate) const -> const Entity*;

    /// Finds entity of the specified type that meets the specified predicate.
    /// @tparam ConcreteEntity Entity type.
    /// @tparam Predicate      Predicate type.
    /// @param  predicate      Predicate.
    /// @return If the set contains entity that meets the specified criteria - a pointer to the entity,
    ///         otherwise - null pointer.
    template<typename ConcreteEntity, typename Predicate>
        requires std::is_base_of_v<Entity, ConcreteEntity>
              && std::is_invocable_r_v<bool, Predicate, const ConcreteEntity&>
    auto findBy(Predicate&& predicate) const -> const ConcreteEntity*;

private:
    EntityListPerKind _entities {}; ///< Mapping entity kinds to lists of entities of that kind.
};

template<typename ConcreteEntity>
    requires std::is_base_of_v<Entity, ConcreteEntity>
auto EntitySet::hasEntityWithQualifiedName(std::string_view name) const noexcept-> bool
{
    return findBy<ConcreteEntity>(Predicates::byQualifiedName(name)) != nullptr;
}

template<typename ConcreteEntity>
    requires std::is_base_of_v<Entity, ConcreteEntity>
auto EntitySet::getEntityWithQualifiedName(std::string_view name) const noexcept-> const ConcreteEntity*
{
    return findBy<ConcreteEntity>(Predicates::byQualifiedName(name));
}

template<typename Predicate>
    requires std::is_invocable_r_v<bool, Predicate, const Entity&>
auto EntitySet::findBy(Predicate&& predicate) const -> const Entity*
{
    for (const auto& [_, entities] : _entities)
    {
        for (const auto& entity : entities)
        {
            if (predicate(*entity))
            {
                return entity.get();
            }
        }
    }
    return nullptr;
}

template<typename ConcreteEntity, typename Predicate>
    requires std::is_base_of_v<Entity, ConcreteEntity>
          && std::is_invocable_r_v<bool, Predicate, const ConcreteEntity&>
auto EntitySet::findBy(Predicate&& predicate) const -> const ConcreteEntity*
{
    if (_entities.contains(EntityTraits<ConcreteEntity>::kind))
    {
        const auto& entities = _entities.at(EntityTraits<ConcreteEntity>::kind);
        for (const auto& entity : entities)
        {
            if (predicate(static_cast<const ConcreteEntity&>(*entity)))
            {
                return static_cast<const ConcreteEntity*>(entity.get());
            }
        }
    }
    return nullptr;
}

} // namespace Prism

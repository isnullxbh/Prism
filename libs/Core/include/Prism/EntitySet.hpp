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

class EntitySet
{
private:
    using EntityList = std::vector<std::unique_ptr<Entity>>;
    using EntityListPerKind = std::unordered_map<EntityKind, EntityList>;

public:
    auto empty() const noexcept -> bool;

    auto size() const noexcept -> std::size_t;

    auto hasEntityWithQualifiedName(std::string_view qualifiedName) const noexcept -> bool;

    template<typename ConcreteEntity>
        requires std::is_base_of_v<Entity, ConcreteEntity>
    auto hasEntityWithQualifiedName(std::string_view name) const noexcept -> bool;

    auto addEntity(std::unique_ptr<Entity> entity) -> void;

private:
    template<typename Predicate>
        requires std::is_invocable_r_v<bool, Predicate, const Entity&>
    auto findBy(Predicate&& predicate) const -> const Entity*;

    template<typename ConcreteEntity, typename Predicate>
        requires std::is_base_of_v<Entity, ConcreteEntity>
              && std::is_invocable_r_v<bool, Predicate, const Entity&>
    auto findBy(Predicate&& predicate) const -> const Entity*;

private:
    EntityListPerKind _entities {};
};

template<typename ConcreteEntity>
    requires std::is_base_of_v<Entity, ConcreteEntity>
auto EntitySet::hasEntityWithQualifiedName(std::string_view name) const noexcept-> bool
{
    return findBy<ConcreteEntity>(Predicates::byQualifiedName(name)) != nullptr;
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
          && std::is_invocable_r_v<bool, Predicate, const Entity&>
auto EntitySet::findBy(Predicate&& predicate) const -> const Entity*
{
    if (_entities.contains(EntityTraits<ConcreteEntity>::kind))
    {
        const auto& entities = _entities.at(EntityTraits<ConcreteEntity>::kind);
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

} // namespace Prism

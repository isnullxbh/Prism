/**
 * @file    EntitySet.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <Prism/EntitySet.hpp>

namespace Prism
{

auto EntitySet::empty() const noexcept-> bool
{
    return _entities.empty();
}

auto EntitySet::size() const noexcept-> std::size_t
{
    std::size_t res {};
    for (const auto& [_, entities] : _entities)
    {
        res += entities.size();
    }
    return res;
}

auto EntitySet::hasEntityWithQualifiedName(std::string_view qualifiedName) const noexcept-> bool
{
    return findBy(Predicates::byQualifiedName(qualifiedName)) != nullptr;
}

auto EntitySet::addEntity(std::unique_ptr<Entity> entity)-> void
{
    _entities[entity->kind()].push_back(std::move(entity));
}

} // namespace Prism

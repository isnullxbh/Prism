/**
 * @file    Entity.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace Prism
{

enum class EntityKind
{
    Class,
    ClassTemplate,
    Enumeration,
    Function,
    FunctionTemplate,
    TypeAlias,
    TypeAliasTemplate,
};

class Entity
{
public:
    virtual ~Entity() = default;
    virtual auto kind() const noexcept -> EntityKind = 0;
    virtual auto name() const noexcept -> const std::string& = 0;
    virtual auto qualifiedName() const noexcept -> const std::string& = 0;
    virtual auto clone() const noexcept -> Entity* = 0;
    virtual auto location() const noexcept -> const std::filesystem::path& = 0;
};

template<typename ConcreteEntity>
struct EntityTraits;

namespace Predicates
{

constexpr inline auto byQualifiedName = [](std::string_view qualifiedName)
{
    return [=](const Entity& entity){ return entity.qualifiedName() == qualifiedName; };
};

} // namespace Predicates
} // namespace Prism

/**
 * @file    AttributeHolder.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <type_traits>
#include <vector>

#include <Prism/Attribute.hpp>
#include <Prism/Utility/Slice.hpp>

namespace clang { class Decl; }

namespace Prism
{

class AttributeHolder
{
public:
    virtual ~AttributeHolder() = default;

    virtual auto getAll() const noexcept -> Slice<const Attribute> = 0;

    template<typename ConcreteAttribute, typename Predicate>
        requires std::is_base_of_v<Attribute, ConcreteAttribute> &&
        std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
    auto contains(Predicate&& predicate) const -> bool;

    template<typename ConcreteAttribute, typename Predicate>
        requires std::is_base_of_v<Attribute, ConcreteAttribute> &&
        std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
    auto find(Predicate&& predicate) const -> const ConcreteAttribute*;

    template<typename ConcreteAttribute, typename Predicate>
        requires std::is_base_of_v<Attribute, ConcreteAttribute> &&
        std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
    auto findAll(Predicate&& predicate) const -> std::vector<const ConcreteAttribute*>;
};

template<typename ConcreteAttribute, typename Predicate>
    requires std::is_base_of_v<Attribute, ConcreteAttribute>
          && std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
auto AttributeHolder::contains(Predicate&& predicate) const -> bool
{
    return find<ConcreteAttribute>(std::forward<Predicate>(predicate)) != nullptr;
}

template<typename ConcreteAttribute, typename Predicate>
    requires std::is_base_of_v<Attribute, ConcreteAttribute>
          && std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
auto AttributeHolder::find(Predicate&& predicate) const -> const ConcreteAttribute*
{
    constexpr auto kind = Attributes::AttributeTraits<ConcreteAttribute>::kind;
    const auto attributes = getAll();
    for (std::size_t i = 0; i < attributes.size(); ++i)
    {
        const auto& attribute = attributes[i];
        if (attribute.kind() == kind && predicate(static_cast<const ConcreteAttribute&>(attribute)))
        {
            return static_cast<const ConcreteAttribute*>(&attribute);
        }
    }
    return nullptr;
}

template<typename ConcreteAttribute, typename Predicate>
    requires std::is_base_of_v<Attribute, ConcreteAttribute>
          && std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
auto AttributeHolder::findAll(Predicate&& predicate) const -> std::vector<const ConcreteAttribute*>
{
    std::vector<const ConcreteAttribute*> res {};

    constexpr auto kind = Attributes::AttributeTraits<ConcreteAttribute>::kind;
    const auto attributes = getAll();
    for (std::size_t i = 0; i < attributes.size(); ++i)
    {
        const auto& attribute = attributes[i];
        if (attribute.kind() == kind && predicate(static_cast<const ConcreteAttribute&>(attribute)))
        {
            res.push_back(static_cast<const ConcreteAttribute*>(&attribute));
        }
    }

    return res;
}

} // namespace Prism

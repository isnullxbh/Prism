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

/// A base class for classes providing information about attributes.
/// @ingroup PrismCore
/// @since   0.1.0
class AttributeHolder
{
public:
    /// Destructor.
    virtual ~AttributeHolder() = default;

    /// Gets a list of all attributes.
    /// @return A sequence of attributes.
    virtual auto getAll() const noexcept -> Slice<const Attribute> = 0;

    /// Check if holder contains attribute of the specified type and it meets the specified predicate.
    /// @tparam ConcreteAttribute Attribute type.
    /// @tparam Predicate         Predicate type.
    /// @param  predicate         Predicate.
    /// @return If holder contains attribute that meets the specified criteria - true, otherwise - false.
    template<typename ConcreteAttribute, typename Predicate>
        requires std::is_base_of_v<Attribute, ConcreteAttribute>
              && std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
    auto contains(Predicate&& predicate) const -> bool;

    /// Finds attribute of the specified type that meets the specified predicate.
    /// @tparam ConcreteAttribute Attribute type.
    /// @tparam Predicate         Predicate type.
    /// @param  predicate         Predicate.
    /// @return If holder contains attribute that meets the specified criteria - a pointer to attribute,
    ///         otherwise - false.
    template<typename ConcreteAttribute, typename Predicate>
        requires std::is_base_of_v<Attribute, ConcreteAttribute>
              && std::is_invocable_r_v<bool, Predicate, const ConcreteAttribute&>
    auto find(Predicate&& predicate) const -> const ConcreteAttribute*;

    /// Finds all attributes of the specified type that meet the specified predicate.
    /// @tparam ConcreteAttribute Attribute type.
    /// @tparam Predicate         Predicate type.
    /// @param  predicate         Predicate.
    /// @return A list of found attributes.
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

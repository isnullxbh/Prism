/**
 * @file    Attribute.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

namespace Prism
{

/// Attribute interface.
/// @ingroup PrismCore
/// @since   0.1.0
class Attribute
{
public:
    /// Defines attribute kinds.
    enum class Kind
    {
        Annotation, ///< Indicates that attribute is a annotate attribute.
    };

    /// Destructor.
    virtual ~Attribute() = default;

    /// Gets the kind of the atribute.
    /// @return Kind.
    virtual auto kind() const noexcept -> Kind = 0;

    /// Creates a copy of the attribute.
    /// A pointer to the created attribute.
    virtual auto clone() const -> Attribute* = 0;
};

namespace Attributes
{

/// An attribute traits.
/// @tparam  ConcreteAttribute Attribute type.
/// @ingroup PrismCore
/// @since   0.1.0
template<typename ConcreteAttribute>
struct AttributeTraits;

} // namespace Attributes
} // namespace Attribute

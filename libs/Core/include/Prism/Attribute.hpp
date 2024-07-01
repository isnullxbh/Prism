/**
 * @file    Attribute.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

namespace Prism
{

class Attribute
{
public:
    enum class Kind
    {
        Annotation,
    };

    virtual ~Attribute() = default;
    virtual auto kind() const noexcept -> Kind = 0;
    virtual auto clone() const -> Attribute* = 0;
};

namespace Attributes
{

template<typename ConcreteAttribute>
struct AttributeTraits;

} // namespace Attributes
} // namespace Attribute

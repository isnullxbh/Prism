/**
 * @file    DefaultAttributeHolder.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <memory>
#include <vector>

#include <Prism/AttributeFactory.hpp>
#include <Prism/AttributeHolder.hpp>

namespace clang { class Decl; }

namespace Prism
{

/// Default implementation of the attribute holder interface.
/// @ingroup PrismCore
/// @since   0.1.0
class DefaultAttributeHolder : public AttributeHolder
{
private:
    /// A type of attribute list.
    using Attributes = std::vector<std::unique_ptr<Attribute>>;

public:
    /// Constructs holder that retrieves attributes from the specified declaration.
    /// @param declaration Declaration to process.
    /// @param factory     Attribute factory.
    explicit DefaultAttributeHolder(const clang::Decl* declaration, AttributeFactory& factory);

    /// Copy constructor.
    /// @param rhs Holder to copy.
    DefaultAttributeHolder(const DefaultAttributeHolder& rhs);

    auto getAll() const noexcept -> Slice<const Attribute> final;

private:
    /// Retrieves attributes from the specified declaration and store them in the current object.
    /// @param declaration Declaration to process.
    /// @param factory     Attribute factory.
    auto init(const clang::Decl* declaration, AttributeFactory& factory) -> void;

    Attributes _attributes {}; ///< Attribute list.
};

} // namespace Prism

/**
 * @file    AttributeFactory.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <memory>
#include <expected>
#include <string>

#include <Prism/Attribute.hpp>

namespace clang { class Attr; }

namespace Prism
{

/// Attribute factory.
/// @ingroup PrismCore
/// @since   0.1.0
class AttributeFactory
{
public:
    /// Destructor.
    virtual ~AttributeFactory() = default;

    /// Creates attribute from the spcified AST node.
    /// @param attribute An AST node corresponding to some attribute.
    /// @return If attribute can be created from the specified AST node - a pointer to the created attribute,
    ///         otherwise - string that contains error message.
    virtual auto create(const clang::Attr* attribute) -> std::expected<std::unique_ptr<Attribute>, std::string>;
};

} // namespace Prism

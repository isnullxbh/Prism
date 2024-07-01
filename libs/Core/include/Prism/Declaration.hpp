/**
 * @file    Declaration.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <Prism/AttributeHolder.hpp>

namespace Prism
{

/// A base class for declarations.
/// @ingroup PrismCore
/// @since   0.1.0
class Declaration
{
public:
    /// Destructor.
    virtual ~Declaration() = default;

    /// Gets an object that provides attribute information.
    /// @return A reference to attribute holder.
    virtual auto attributes() const noexcept -> const AttributeHolder& = 0;
};

} // namespace Prism

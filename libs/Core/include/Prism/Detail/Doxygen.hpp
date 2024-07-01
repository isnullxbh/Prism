/**
 * @file    Doxygen.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#pragma once

/// @defgroup Prism Prism

/// @defgroup PrismCore Core
/// Provides core components.
/// @ingroup  Prism

/// @defgroup PrismCoreMatchers Entity matchers
/// Matchers used to find entity of concrete kinds.
/// @ingroup  PrismCore

/// @defgroup PrismCoreAttributes Attributes
/// Supported attributes.
/// @ingroup  PrismCore

/// @defgroup PrismCoreEntities Entities
/// Supported entities.
/// @ingroup  PrismCore

/// Top-level library namespace.
namespace Prism
{
    /// Contains frequently used predicates.
    namespace Predicates
    {}

    /// Contains attributes.
    namespace Attributes
    {
        /// Contains frequently used predicates related to attributes.
        namespace Predicates
        {}
    }
}

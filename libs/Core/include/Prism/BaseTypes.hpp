/**
 * @file    BaseTypes.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

#include <exception>

/// @todo: use forward declaration
#include <clang/Basic/Specifiers.h>

namespace Prism
{

/// Defines access specifiers.
/// @ingroup PrismCore
/// @since   0.1.0
enum class Accessibility
{
    Public,     ///< Indicates public access for class member or public inheritance.
    Protected,  ///< Indicates protected access for class member or protected inheritance.
    Private     ///< Indicates private access for class member or private inheritance.
};

/// Converts Clang-based access specifier to project-based access specifier.
/// @param   specifier Clang-based access specifier.
/// @return  Project-based access specifier.
/// @ingroup PrismCore
/// @since   0.1.0
/// @throws  std::runtime_error Will be thrown if the speicifed access specifier is not defined.
/// @todo    Move to source file.
constexpr auto convertToAccessibility(clang::AccessSpecifier specifier) -> Accessibility
{
    switch (specifier)
    {
        case clang::AccessSpecifier::AS_public:
            return Accessibility::Public;

        case clang::AccessSpecifier::AS_protected:
            return Accessibility::Protected;

        case clang::AccessSpecifier::AS_private:
            return Accessibility::Private;

        default:
            throw std::runtime_error("Unknown specifier");
    }
}

} // namespace Prism

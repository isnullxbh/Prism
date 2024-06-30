/**
 * @file    BaseTypes.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

#include <exception>

#include <clang/Basic/Specifiers.h>

namespace Prism
{

enum class Accessibility
{
    Public,
    Protected,
    Private
};

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

/**
 * @file    ClassMember.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

#include <string>

#include <Prism/BaseTypes.hpp>
#include <Prism/Declaration.hpp>

namespace Prism
{

/// Class member interface.
/// @ingroup PrismCore
/// @since   0.1.0
class ClassMember : public Declaration
{
public:
    /// Defines class member kinds.
    enum class Kind
    {
        DataMember,     ///< Indicates that member is a data member.
        MemberFunction, ///< Indicates that member is a member function.
    };

    /// Gets the kind of the class member.
    /// @return Kind.
    virtual constexpr auto kind() const noexcept -> Kind = 0;

    /// Gets the name of the class member.
    /// @return A string that contains class member name.
    virtual auto name() const noexcept -> const std::string& = 0;

    /// Gets the type of the class member.
    /// @return A string that contains human-readable representation of the class member type.
    virtual auto type() const noexcept -> const std::string& = 0;

    /// Gets the access specifier for the class member.
    /// @return Access specifier.
    virtual auto accessibility() const noexcept -> Accessibility = 0;
};

} // namespace Prism

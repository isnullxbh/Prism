/**
 * @file    ClassMember.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

#include <string>

#include <Prism/BaseTypes.hpp>

namespace Prism
{

class ClassMember
{
public:
    enum class Kind
    {
        DataMember,
        MemberFunction,
    };

    virtual ~ClassMember() = default;
    virtual constexpr auto kind() const noexcept -> Kind = 0;
    virtual auto name() const noexcept -> const std::string& = 0;
    virtual auto type() const noexcept -> const std::string& = 0;
    virtual auto accessibility() const noexcept -> Accessibility = 0;
};

} // namespace Prism

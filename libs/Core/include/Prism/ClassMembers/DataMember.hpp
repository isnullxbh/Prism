/**
 * @file    DataMember.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

#include <clang/AST/DeclCXX.h>

#include <Prism/ClassMember.hpp>

namespace Prism
{

class DataMember : public ClassMember
{
public:
    explicit DataMember(const clang::FieldDecl* declaration);

    constexpr auto kind() const noexcept -> Kind final { return Kind::DataMember; }
    auto name() const noexcept -> const std::string& final;
    auto type() const noexcept -> const std::string& final;
    auto accessibility() const noexcept -> Accessibility final;

private:
    std::string   _name;
    std::string   _type;
    Accessibility _accessibility;
};

} // namespace Prism

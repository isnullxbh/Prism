/**
 * @file    EntityBase.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <clang/AST/DeclCXX.h>

#include <Prism/Entity.hpp>

namespace Prism
{

class EntityBase : public Entity
{
public:
    auto name() const noexcept -> const std::string& final;
    auto qualifiedName() const noexcept -> const std::string& final;
    auto location() const noexcept -> const std::filesystem::path& final;

protected:
    explicit EntityBase(const clang::NamedDecl* declaration);

private:
    std::string           _name;
    std::string           _qualified_name;
    std::filesystem::path _location;
};

} // namespace Prism

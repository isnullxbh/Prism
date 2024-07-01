/**
 * @file    EntityBase.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <Prism/Entity.hpp>
#include <Prism/AttributeFactory.hpp>
#include <Prism/DefaultAttributeHolder.hpp>

namespace clang { class NamedDecl; }

namespace Prism
{

class EntityBase : public Entity
{
public:
    auto attributes() const noexcept -> const AttributeHolder& final;
    auto name() const noexcept -> const std::string& final;
    auto qualifiedName() const noexcept -> const std::string& final;
    auto location() const noexcept -> const std::filesystem::path& final;

protected:
    explicit EntityBase(const clang::NamedDecl* declaration, AttributeFactory& attribute_factory);

private:
    std::string            _name;
    std::string            _qualified_name;
    std::filesystem::path  _location;
    DefaultAttributeHolder _attributes_holder;
};

} // namespace Prism

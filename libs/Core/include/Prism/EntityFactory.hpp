/**
 * @file    EntityFactory.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#pragma once

#include <memory>

#include <Prism/Entity.hpp>
#include <Prism/AttributeFactory.hpp>

namespace clang { class Decl; }

namespace Prism
{

class EntityFactory
{
public:
    EntityFactory();
    explicit EntityFactory(std::unique_ptr<AttributeFactory> attribute_factory);
    virtual ~EntityFactory() = default;
    virtual auto create(const clang::Decl* declaration) -> std::unique_ptr<Entity>;

private:
    std::unique_ptr<AttributeFactory> _attribute_factory;
};

} // namespace Prism

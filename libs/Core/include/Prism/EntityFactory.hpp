/**
 * @file    EntityFactory.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#pragma once

#include <memory>

#include <clang/AST/Decl.h>

#include <Prism/Entity.hpp>

namespace Prism
{

class EntityFactory
{
public:
    virtual ~EntityFactory() = default;
    virtual auto create(const clang::Decl* declaration) -> std::unique_ptr<Entity>;
};

} // namespace Prism

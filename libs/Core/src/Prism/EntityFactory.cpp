/**
 * @file    EntityFactory.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#include <Prism/EntityFactory.hpp>

#include <exception>

#include <clang/AST/Decl.h>

#include <Prism/Entities/Class.hpp>

namespace Prism
{

EntityFactory::EntityFactory()
    : _attribute_factory(std::make_unique<AttributeFactory>())
{}

EntityFactory::EntityFactory(std::unique_ptr<AttributeFactory> attribute_factory)
    : _attribute_factory(std::move(attribute_factory))
{}

auto EntityFactory::create(const clang::Decl* declaration)-> std::unique_ptr<Entity>
{
    std::unique_ptr<Entity> entity {};

    switch (declaration->getKind())
    {
        case clang::Decl::Kind::CXXRecord:
            entity = std::make_unique<Class>(clang::dyn_cast<clang::CXXRecordDecl>(declaration), std::ref(*_attribute_factory));
            break;

        default:
            throw std::runtime_error("Unknown declaration");
    }

    return entity;
}

} // namespace Prism

/**
 * @file    EntityFactory.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#include <Prism/EntityFactory.hpp>

#include <exception>

#include <Prism/Entities/Class.hpp>

namespace Prism
{

auto EntityFactory::create(const clang::Decl* declaration)-> std::unique_ptr<Entity>
{
    std::unique_ptr<Entity> entity {};

    switch (declaration->getKind())
    {
        case clang::Decl::Kind::CXXRecord:
            entity = std::make_unique<Class>(clang::dyn_cast<clang::CXXRecordDecl>(declaration));
            break;

        default:
            throw std::runtime_error("Unknown declaration");
    }

    return entity;
}

} // namespace Prism

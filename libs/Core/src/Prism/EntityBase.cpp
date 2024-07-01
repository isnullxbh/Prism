/**
 * @file    EntityBase.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#include <Prism/EntityBase.hpp>

#include <clang/AST/ASTContext.h>
#include <clang/AST/DeclCXX.h>

namespace Prism
{

auto EntityBase::attributes() const noexcept -> const AttributeHolder&
{
    return _attributes_holder;
}

auto EntityBase::name() const noexcept-> const std::string&
{
    return _name;
}

auto EntityBase::qualifiedName() const noexcept-> const std::string&
{
    return _qualified_name;
}

auto EntityBase::location() const noexcept-> const std::filesystem::path&
{
    return _location;
}

EntityBase::EntityBase(const clang::NamedDecl* declaration, AttributeFactory& attribute_factory)
    : _name(declaration->getName())
    , _qualified_name(declaration->getQualifiedNameAsString())
    , _attributes_holder(declaration, attribute_factory)
{
    const auto& source_manager = declaration->getASTContext().getSourceManager();
    _location = declaration->getLocation().printToString(source_manager);
}

} // namespace Prism

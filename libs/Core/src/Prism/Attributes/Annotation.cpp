/**
 * @file    Annotation.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#include <Prism/Attributes/Annotation.hpp>

#include <clang/AST/Attr.h>

namespace Prism::Attributes
{

Annotation::Annotation(const clang::AnnotateAttr* attribute)
    : _text(attribute->getAnnotation().str())
{}

auto Annotation::kind() const noexcept -> Kind
{
    return Kind::Annotation;
}

auto Annotation::clone() const -> Attribute*
{
    return new Annotation(*this);
}

auto Annotation::text() const noexcept -> const std::string&
{
    return _text;
}

} // namespace Prism::Attributes

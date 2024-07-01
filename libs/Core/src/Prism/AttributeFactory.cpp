/**
 * @file    AttributeFactory.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#include <Prism/AttributeFactory.hpp>

#include <clang/AST/Attr.h>

#include <Prism/Attributes/Annotation.hpp>

namespace Prism
{

auto AttributeFactory::create(const clang::Attr* attribute) -> std::expected<std::unique_ptr<Attribute>, std::string>
{
    switch (attribute->getKind())
    {
        case clang::attr::Annotate:
            return std::make_unique<Attributes::Annotation>(static_cast<const clang::AnnotateAttr*>(attribute));

        default:
            return std::unexpected("Unknown attribute kind");
    }
}

} // namespace Prism

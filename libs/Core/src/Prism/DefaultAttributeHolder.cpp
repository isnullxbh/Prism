/**
 * @file    DefaultAttributeHolder.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#include <Prism/DefaultAttributeHolder.hpp>

#include <clang/AST/Decl.h>

namespace Prism
{

DefaultAttributeHolder::DefaultAttributeHolder(const clang::Decl* declaration, AttributeFactory& factory)
{
    init(declaration, factory);
}

DefaultAttributeHolder::DefaultAttributeHolder(const DefaultAttributeHolder& rhs)
{
    for (const auto& attribute : rhs._attributes)
    {
        _attributes.emplace_back(attribute->clone());
    }
}

static constexpr auto from_ptr = [](const std::unique_ptr<Attribute>* ptr) -> Attribute*
{
    return ptr->get();
};

auto DefaultAttributeHolder::getAll() const noexcept -> Slice<const Attribute>
{
    return Slice<const Attribute> { _attributes.data(), _attributes.size(), from_ptr };
}

auto DefaultAttributeHolder::init(const clang::Decl* declaration, AttributeFactory& factory) -> void
{
    for (auto it = declaration->attr_begin(); it != declaration->attr_end(); ++it)
    {
        if (auto createAttribute = factory.create(*it))
        {
            _attributes.push_back(std::move(createAttribute).value());
        }
    }
}

} // namespace Prism

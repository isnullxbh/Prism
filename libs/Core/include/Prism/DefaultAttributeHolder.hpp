/**
 * @file    DefaultAttributeHolder.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <memory>
#include <vector>

#include <Prism/AttributeFactory.hpp>
#include <Prism/AttributeHolder.hpp>

namespace clang { class Decl; }

namespace Prism
{

class DefaultAttributeHolder : public AttributeHolder
{
private:
    using Attributes = std::vector<std::unique_ptr<Attribute>>;

public:
    explicit DefaultAttributeHolder(const clang::Decl* declaration, AttributeFactory& factory);
    DefaultAttributeHolder(const DefaultAttributeHolder& rhs);
    auto getAll() const noexcept -> Slice<const Attribute> final;

private:
    auto init(const clang::Decl* declaration, AttributeFactory& factory) -> void;

    Attributes _attributes {};
};

} // namespace Prism

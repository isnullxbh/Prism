/**
 * @file    AttributeFactory.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <memory>
#include <expected>
#include <string>

#include <Prism/Attribute.hpp>

namespace clang { class Attr; }

namespace Prism
{

class AttributeFactory
{
public:
    virtual ~AttributeFactory() = default;
    virtual auto create(const clang::Attr* attribute) -> std::expected<std::unique_ptr<Attribute>, std::string>;
};

} // namespace Prism

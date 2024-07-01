/**
 * @file    Declaration.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <Prism/AttributeHolder.hpp>

namespace Prism
{

class Declaration
{
public:
    virtual ~Declaration() = default;
    virtual auto attributes() const noexcept -> const AttributeHolder& = 0;
};

} // namespace Prism

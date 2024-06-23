/**
 * @file    Class.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <Prism/EntityBase.hpp>

namespace Prism
{

class Class : public EntityBase
{
public:
    explicit Class(const clang::CXXRecordDecl* declaration);
    auto kind() const noexcept -> EntityKind override;
    auto clone() const noexcept -> Class* override;

protected:
    Class(const Class&) = default;
};

template<>
struct EntityTraits<Class>
{
    static constexpr auto kind = EntityKind::Class;
};

} // namespace Prism

/**
 * @file    Class.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <vector>

#include <Prism/EntityBase.hpp>
#include <Prism/ClassMembers/DataMember.hpp>

namespace Prism
{

class Class : public EntityBase
{
public:
    using DataMembers = std::vector<DataMember>;

    explicit Class(const clang::CXXRecordDecl* declaration);
    auto kind() const noexcept -> EntityKind override;
    auto clone() const noexcept -> Class* override;

    auto dataMembers() const noexcept -> const DataMembers&;

private:
    Class(const Class&) = default;

    static auto extractDataMembers(const clang::CXXRecordDecl* declaration, DataMembers& members) -> void;

    DataMembers _data_members {};
};

template<>
struct EntityTraits<Class>
{
    static constexpr auto kind = EntityKind::Class;
};

} // namespace Prism

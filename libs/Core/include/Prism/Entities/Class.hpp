/**
 * @file    Class.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <vector>

#include <Prism/EntityBase.hpp>
#include <Prism/ClassMembers/DataMember.hpp>
#include <Prism/AttributeFactory.hpp>

namespace Prism
{

/// Class.
/// @ingroup PrismCoreEntities
/// @since   0.1.0
class Class : public EntityBase
{
public:
    /// A type of data member list.
    using DataMembers = std::vector<DataMember>;

    /// Constructs class from the specified declaration.
    /// @param declaration       A class declaration.
    /// @param attribute_factory Attribute factory.
    explicit Class(const clang::CXXRecordDecl* declaration, AttributeFactory& attribute_factory);

    auto kind() const noexcept -> EntityKind override;
    auto clone() const noexcept -> Class* override;

    /// Gets the data members.
    /// @return A data member list.
    auto dataMembers() const noexcept -> const DataMembers&;

private:
    /// Copy constructor.
    Class(const Class&) = default;

    /// Retrieves data members from the specified class declaration and store them in the current object.
    /// @param declaration A class declaration.
    /// @param factory     Attribute factory.
    /// @param members     A reference to data member list.
    static auto extractDataMembers(const clang::CXXRecordDecl* declaration, AttributeFactory& factory, DataMembers& members) -> void;

    DataMembers _data_members {}; ///< Data members.
};

/// A specialization of the EntityTraits class template for classes.
/// @ingroup PrismCoreEntities
/// @since   0.1.0
template<>
struct EntityTraits<Class>
{
    static constexpr auto kind = EntityKind::Class;
};

} // namespace Prism

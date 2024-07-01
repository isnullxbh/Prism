/**
 * @file    EntityFactory.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.06.2024
 */

#pragma once

#include <memory>

#include <Prism/Entity.hpp>
#include <Prism/AttributeFactory.hpp>

namespace clang { class Decl; }

namespace Prism
{

/// Entity factory.
/// @ingroup PrismCore
/// @since   0.1.0
class EntityFactory
{
public:
    /// Constructs entity factory with default attribute factory.
    EntityFactory();

    /// Constructs entity factory with the specified attribute factory.
    /// @param attribute_factory Attribute factory.
    explicit EntityFactory(std::unique_ptr<AttributeFactory> attribute_factory);

    /// Destructor.
    virtual ~EntityFactory() = default;

    /// Creates entity from the specified declaration.
    /// @param  declaration Entity declaration.
    /// @return A pointer to the created entity.
    [[nodiscard]] virtual auto create(const clang::Decl* declaration) -> std::unique_ptr<Entity>;

private:
    std::unique_ptr<AttributeFactory> _attribute_factory; ///< Attribute factory.
};

} // namespace Prism

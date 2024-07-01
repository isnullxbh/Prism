/**
 * @file    Annotation.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <string>
#include <string_view>

#include <Prism/Attribute.hpp>

namespace clang { class AnnotateAttr; }

namespace Prism::Attributes
{

/// Annotate attribute.
/// @ingroup PrismCoreAttributes
/// @since   0.1.0
class Annotation : public Attribute
{
public:
    /// Constructs annotate attribute from the specified AST node.
    /// @param attribute An AST node corresponding to annotate attribute.
    explicit Annotation(const clang::AnnotateAttr* attribute);

    auto kind() const noexcept -> Kind final;

    auto clone() const -> Attribute* final;

    /// Gets the text of the annotate attribute.
    /// @return A string that contains annotation.
    auto text() const noexcept -> const std::string&;

private:
    std::string _text; ///< Annotation text.
};

/// A specialization of the AttributeTraits class template for annotate attributes.
/// @ingroup PrismCoreAttributes
/// @since   0.1.0
template<>
struct AttributeTraits<Annotation>
{
    static constexpr Attribute::Kind kind = Attribute::Kind::Annotation;
};

namespace Predicates
{

/// Creates a predicate to find annotations by text.
inline auto annotationWithText = [](std::string_view text)
{
    return [=](const Annotation& annotation)
    {
        return annotation.text() == text;
    };
};

} // namespace Predicates
} // namespace Prism::Attributes

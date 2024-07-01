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

class Annotation : public Attribute
{
public:
    explicit Annotation(const clang::AnnotateAttr* attribute);
    auto kind() const noexcept -> Kind final;
    auto clone() const -> Attribute* final;
    auto text() const noexcept -> const std::string&;

private:
    std::string _text;
};

template<>
struct AttributeTraits<Annotation>
{
    static constexpr Attribute::Kind kind = Attribute::Kind::Annotation;
};

namespace Predicates
{

inline auto annotationWithText = [](std::string_view text)
{
    return [=](const Annotation& annotation)
    {
        return annotation.text() == text;
    };
};

} // namespace Predicates
} // namespace Prism::Attributes

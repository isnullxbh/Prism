/**
 * @file    Matchers.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.06.2024
 */

#pragma once

#include <clang/ASTMatchers/ASTMatchers.h>

namespace Prism
{

/// Matcher for classes.
/// @ingroup PrismCoreMatchers
/// @since   0.1.0
inline const auto class_matcher =
    clang::ast_matchers::cxxRecordDecl(
        // Skip primary class template
        clang::ast_matchers::unless(clang::ast_matchers::hasParent(clang::ast_matchers::classTemplateDecl())),
        // Skip class template specializations
        clang::ast_matchers::unless(clang::ast_matchers::isExplicitTemplateSpecialization()),
        // Skip forward declarations
        clang::ast_matchers::isDefinition());
} // namespace Prism

/**
 * @file    ClassMatchCallback.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#pragma once

#include <Prism/MatchCallbackBase.hpp>

namespace Prism
{

class ClassMatchCallback
    : public MatchCallbackBase<clang::CXXRecordDecl>
{
public:
    using MatchCallbackBase::MatchCallbackBase;

    auto run(const clang::ast_matchers::MatchFinder::MatchResult& result) -> void override;
};

} // namespace Prism

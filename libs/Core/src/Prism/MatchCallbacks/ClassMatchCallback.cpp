/**
 * @file    ClassMatchCallback.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#include <Prism/MatchCallbacks/ClassMatchCallback.hpp>

#include <clang/AST/DeclCXX.h>

#include <Prism/Entities/Class.hpp>

namespace Prism
{

auto ClassMatchCallback::run(const clang::ast_matchers::MatchFinder::MatchResult& result)-> void
{
    if (const auto declaration = result.Nodes.getNodeAs<clang::CXXRecordDecl>(id()))
    {
        entitySet()->addEntity(std::make_unique<Class>(declaration));
    }
}

} // namespace Prism

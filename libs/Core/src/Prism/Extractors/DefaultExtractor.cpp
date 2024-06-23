/**
 * @file    DefaultExtractor.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#include <Prism/Extractors/DefaultExtractor.hpp>

#include <algorithm>
#include <vector>
#include <exception>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/CompilerInstance.h>

namespace Prism
{

DefaultExtractor::DefaultExtractor(MatcherSet matchers)
    : _pch_ops(std::make_shared<clang::PCHContainerOperations>())
    , _diagnostic_engine(clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions()))
    , _matchers(std::move(matchers))
{
}

auto DefaultExtractor::extract(const std::filesystem::path& path)-> EntitySet
{
    return extract(path, Parameters());
}

auto DefaultExtractor::extract(const std::filesystem::path& path, const Parameters& parameters)-> EntitySet
{
    _diagnostic_engine->Clear();

    const auto parameter_list = parameters.toList();
    const auto path_as_string = path.generic_string();

    std::vector<const char*> args {};
    args.push_back("dummy");
    std::transform(parameter_list.cbegin(), parameter_list.cend(), std::back_inserter(args), [](const std::string& s)
        { return s.data(); });
    args.push_back(path_as_string.data());

    auto unit =
        clang::ASTUnit::LoadFromCommandLine(args.data(), args.data() + args.size(),
            _pch_ops,
            _diagnostic_engine,
            llvm::StringRef(),
            false,
            llvm::StringRef(),
            false,
            clang::CaptureDiagsKind::None,
            std::nullopt,
            true,
            0,
            clang::TranslationUnitKind::TU_Complete,
            false,
            false,
            false,
            clang::SkipFunctionBodiesScope::PreambleAndMainFile);

    if (!unit || _diagnostic_engine->getNumErrors() > 0)
    {
        throw std::runtime_error ("An error occurred while parsing sources");
    }

    EntitySet entities {};
    setUpCallbacks(entities);

    clang::ast_matchers::MatchFinder finder {};
    addMatchersTo(finder);
    finder.matchAST(unit->getASTContext());

    return entities;
}

auto DefaultExtractor::setUpCallbacks(EntitySet& entities)-> void
{
    using clang::ast_matchers::DeclarationMatcher;

    _matchers.for_each([&](DeclarationMatcher&, MatchCallback& callback)
    {
        callback.setEntitySet(entities);
    });
}

auto DefaultExtractor::addMatchersTo(clang::ast_matchers::MatchFinder& finder)-> void
{
    using clang::ast_matchers::DeclarationMatcher;

    _matchers.for_each([&finder](DeclarationMatcher& matcher, MatchCallback& callback)
    {
        finder.addMatcher(matcher, &callback);
    });
}

} // namespace Prism

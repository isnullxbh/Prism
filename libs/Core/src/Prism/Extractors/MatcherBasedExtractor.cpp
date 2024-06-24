/**
 * @file    MatcherBasedExtractor.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#include <Prism/Extractors/MatcherBasedExtractor.hpp>

#include <algorithm>
#include <vector>
#include <exception>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/CompilerInstance.h>

namespace Prism
{

MatcherBasedExtractor::MatcherBasedExtractor()
    : _pch_ops(std::make_shared<clang::PCHContainerOperations>())
    , _diagnostic_engine(clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions()))
    , _entity_factory(std::make_unique<EntityFactory>())
{
}

MatcherBasedExtractor::MatcherBasedExtractor(std::unique_ptr<EntityFactory> factory)
    : _pch_ops(std::make_shared<clang::PCHContainerOperations>())
    , _diagnostic_engine(clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions()))
    , _entity_factory(std::move(factory))
{
}

auto MatcherBasedExtractor::extract(const std::filesystem::path& path)-> EntitySet
{
    return extract(path, Parameters());
}

auto MatcherBasedExtractor::extract(const std::filesystem::path& path, const Parameters& parameters)-> EntitySet
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

    clang::ast_matchers::MatchFinder finder {};
    std::vector<std::unique_ptr<clang::ast_matchers::MatchFinder::MatchCallback>> callbacks {};
    for (auto& entry : _matcher_entries)
    {
        callbacks.push_back(entry.create_match_callback(entities));
        finder.addMatcher(entry.matcher, callbacks.back().get());
    }

    finder.matchAST(unit->getASTContext());

    return entities;
}

} // namespace Prism

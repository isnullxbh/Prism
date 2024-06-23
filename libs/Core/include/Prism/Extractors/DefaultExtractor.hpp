/**
 * @file    DefaultExtractor.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/Serialization/PCHContainerOperations.h>

#include <Prism/Extractor.hpp>
#include <Prism/MatcherSet.hpp>

namespace Prism
{

class DefaultExtractor : public Extractor
{
public:
    using Extractor::Parameters;

    explicit DefaultExtractor(MatcherSet matchers);

    auto extract(const std::filesystem::path& path) -> EntitySet override;
    auto extract(const std::filesystem::path& path, const Parameters& parameters) -> EntitySet override;

private:
    auto setUpCallbacks(EntitySet& entities) -> void;
    auto addMatchersTo(clang::ast_matchers::MatchFinder& finder) -> void;

    std::shared_ptr<clang::PCHContainerOperations>      _pch_ops;
    clang::IntrusiveRefCntPtr<clang::DiagnosticsEngine> _diagnostic_engine;
    MatcherSet                                          _matchers;
};

} // namespace Prism

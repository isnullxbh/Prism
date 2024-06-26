/**
 * @file    MatcherBasedExtractor.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/Serialization/PCHContainerOperations.h>

#include <Prism/EntityFactory.hpp>
#include <Prism/Extractor.hpp>
#include <Prism/MatchCallback.hpp>

namespace Prism
{

/// Entity metadata extractor based on AST node matchers.
/// @ingroup PrismCore
/// @since   0.1.0
class MatcherBasedExtractor : public Extractor
{
private:
    /// Type of function used to create match callback.
    using MatchCallbackCreator = std::function<std::unique_ptr<clang::ast_matchers::MatchFinder::MatchCallback>(EntitySet&)>;

    /// Contains matcher, it's ID and function used to create corresponding match callback.
    struct MatcherEntry
    {
        std::string                             id;                     ///< ID.
        clang::ast_matchers::DeclarationMatcher matcher;                ///< Matcher.
        MatchCallbackCreator                    create_match_callback;  ///< Function used to create match callback.
    };

    /// A type of matcher entry list.
    using MatcherEntries = std::vector<MatcherEntry>;

    /// A match callback for the speicifed declaration type.
    /// @tparam Declaration
    template<typename Declaration>
    class Callback;

public:
    using Extractor::Parameters;
    using BindableDeclarationMatcher = clang::ast_matchers::internal::BindableMatcher<clang::Decl>;

    /// Constructs extractor with the default entity factory.
    MatcherBasedExtractor();

    /// Constructs extractor with the specified entity factory.
    /// @param factory Entity factory.
    explicit MatcherBasedExtractor(std::unique_ptr<EntityFactory> factory);

    /// Adds the specified matcher to the extractor.
    /// @tparam Declaration A declaration type compatible with the specified matcher.
    /// @param  matcher     Matcher.
    template<typename Declaration>
        requires std::is_base_of_v<clang::NamedDecl, Declaration>
    auto addMatcher(BindableDeclarationMatcher matcher) -> void;

    /// Extracts entities from source file with the specified path.
    /// @param  path Source file path.
    /// @return An entity set.
    auto extract(const std::filesystem::path& path) -> EntitySet override;

    /// Extracts entities from source file with the specifeid path according to the specified parameters.
    /// @param  path       Source file path.
    /// @param  parameters Extraction parameters.
    /// @return An entity set.
    auto extract(const std::filesystem::path& path, const Parameters& parameters) -> EntitySet override;

private:
    std::shared_ptr<clang::PCHContainerOperations>      _pch_ops;
    clang::IntrusiveRefCntPtr<clang::DiagnosticsEngine> _diagnostic_engine;
    std::unique_ptr<EntityFactory>                      _entity_factory;
    MatcherEntries                                      _matcher_entries   {};
    std::size_t                                         _index             {};
};

template<typename Declaration>
class MatcherBasedExtractor::Callback final : public MatchCallback<Declaration>
{
public:
    explicit Callback(std::string_view id, EntityFactory& factory, EntitySet& entities)
        : MatchCallback<Declaration>(id)
        , _factory(&factory)
        , _entities(&entities)
    {}

private:
    auto consume(const Declaration* declaration) -> void
    {
        _entities->addEntity(_factory->create(declaration));
    }

    EntityFactory* _factory;
    EntitySet*     _entities;
};

template<typename Declaration>
    requires std::is_base_of_v<clang::NamedDecl, Declaration>
auto MatcherBasedExtractor::addMatcher(BindableDeclarationMatcher matcher)-> void
{
    const auto id = std::format("e{}", _index++);

    _matcher_entries.emplace_back(id, std::move(matcher).bind(id), [&, id = id, this](EntitySet& entities)
    {
        return std::make_unique<Callback<Declaration>>(id, std::ref(*_entity_factory), std::ref(entities));
    });
}

} // namespace Prism

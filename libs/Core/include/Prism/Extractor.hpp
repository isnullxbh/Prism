/**
 * @file    Extractor.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <Prism/EntitySet.hpp>

namespace Prism
{

/// Extracts entity metadata from source code.
/// @ingroup PrismCore
/// @since   0.1.0
class Extractor
{
public:
    /// Extraction parameters.
    class Parameters
    {
    public:
        /// Destructor.
        virtual ~Parameters() = default;

        /// Add include path.
        /// This path will be used to search for headers during preprocessing.
        /// @param path Include path.
        auto addIncludePath(std::filesystem::path path) -> void;

        /// Converts all parameters to strings and store them in a list.
        /// @return Created list.
        virtual auto toList() const -> std::vector<std::string>;

    private:
        std::vector<std::filesystem::path> _include_paths {}; ///< Include paths.
    };

    /// Destructor.
    virtual ~Extractor() = default;

    /// Extracts entity metadata from source file with the specified path.
    /// @param  path Path to source file.
    /// @return A set of extracted entities.
    virtual auto extract(const std::filesystem::path& path) -> EntitySet = 0;

    /// Extracts entity metadata from source file with the specified path.
    /// @param  path       Path to source file.
    /// @param  parameters Extraction parameters.
    /// @return A set of extracted entities.
    virtual auto extract(const std::filesystem::path& path, const Parameters& parameters) -> EntitySet = 0;
};

} // namespace Prism

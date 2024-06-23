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

class Extractor
{
public:
    class Parameters
    {
    public:
        virtual ~Parameters() = default;
        auto addIncludePath(std::filesystem::path path) -> void;
        virtual auto toList() const -> std::vector<std::string>;

    private:
        std::vector<std::filesystem::path> _include_paths {};
    };

    virtual ~Extractor() = default;
    virtual auto extract(const std::filesystem::path& path) -> EntitySet = 0;
    virtual auto extract(const std::filesystem::path& path, const Parameters& parameters) -> EntitySet = 0;
};

} // namespace Prism

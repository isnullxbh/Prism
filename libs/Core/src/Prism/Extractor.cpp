/**
 * @file    Extractor.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.06.2024
 */

#include <Prism/Extractor.hpp>

#include <algorithm>

namespace Prism
{

auto Extractor::Parameters::addIncludePath(std::filesystem::path path)-> void
{
    _include_paths.push_back(std::move(path));
}

auto Extractor::Parameters::toList() const-> std::vector<std::string>
{
    std::vector<std::string> res {};

    std::transform(_include_paths.cbegin(), _include_paths.cend(), std::back_inserter(res),
        [](const std::filesystem::path& path){ return "-I" + path.generic_string(); });

    return res;
}

} // namespace Prism

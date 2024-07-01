/**
 * @file    Slice.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.07.2024
 */

#pragma once

#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

namespace Prism
{

template<typename T>
class Slice
{
public:
    explicit Slice(T* data, std::size_t size);

    template<typename Mapper, typename U>
        requires std::is_invocable_r_v<T*, Mapper, U*>
    explicit Slice(U* data, std::size_t size, Mapper&& mapper)
        : _data(nullptr)
        , _size(size)
    {
        // TODO
        _init = [base = data, mapper = std::forward<Mapper>(mapper), this](std::size_t index)
        {
            _data = mapper(base + index);
        };
    }

    auto size() const noexcept -> std::size_t;

    auto operator[](std::size_t index) const -> T&;

private:
    T*                               _data;
    std::size_t                      _size;
    std::function<void(std::size_t)> _init { nullptr };
};

template<typename T>
Slice(T*, std::size_t) -> Slice<T>;

template<typename T>
Slice<T>::Slice(T* data, std::size_t size)
    : _data(data)
    , _size(size)
{}

template<typename T>
auto Slice<T>::size() const noexcept -> std::size_t
{
    return _size;
}

template<typename T>
auto Slice<T>::operator[](std::size_t index) const -> T&
{
    if (_init)
    {
        _init(index);
    }

    return _data[index];
}

} // namespace Prism

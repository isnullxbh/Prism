/**
 * @file    Templates.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.06.2024
 */

#pragma once

class                      A1      {}; // Regular class

template<typename T> class A2      {}; // Class template
template<> class           A2<int> {}; // Full specialization
template<typename T> class A2<T*>  {}; // Partial specialization

A2<char> a2 {};

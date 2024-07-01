/**
 * @file    Members.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    30.06.2024
 */

#pragma once

namespace N1
{
    class T1 {};
    class T2 {};
}

class [[clang::annotate("Class1")]] Class
{
public:
    [[clang::annotate("Field1")]]
    int                 m1;

    [[clang::annotate("Field2")]]
    static const N1::T1 m2;

private:
    [[clang::annotate("Field3")]]
    N1::T2              m3;

    [[clang::annotate("Field4")]]
    static const int    m4;
};

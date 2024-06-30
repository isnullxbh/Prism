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

class Class
{
public:
    int                 m1;
    static const N1::T1 m2;

private:
    N1::T2              m3;
    static const int    m4;
};

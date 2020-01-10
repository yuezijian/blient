//
// Created by 岳子剑 on 2020/01/09.
//


#ifndef BLIENT__BASE__PROGRAM__HPP
#define BLIENT__BASE__PROGRAM__HPP


#include "Version.hpp"


class Program
{
public:
    virtual ~Program() = default;

    virtual int Main( int argc, char* argv[] ) = 0;

    [[nodiscard]] virtual Version InstanceVersion() const = 0;
};


#endif

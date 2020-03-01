//
// Created by 岳子剑 on 2020/01/09.
//


#include "Client.hpp"


extern "C" BLIENT_CLIENT__EXPORT Program* CreateProgram()
{
    return new Client;
}

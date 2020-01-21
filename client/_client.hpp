//
// Created by 岳子剑 on 2020/01/09.
//


#ifndef BLIENT__CLIENT__HPP
#define BLIENT__CLIENT__HPP


#ifndef BLIENT_CLIENT__API

    #if WIN32

        #define BLIENT_CLIENT__EXPORT __declspec(dllexport)
        #define BLIENT_CLIENT__IMPORT __declspec(dllimport)

    #else

        #define BLIENT_CLIENT__EXPORT __attribute__((visibility( "default")))
        #define BLIENT_CLIENT__IMPORT __attribute__((visibility( "default")))

    #endif

    #define BLIENT_CLIENT__API

#endif


#endif

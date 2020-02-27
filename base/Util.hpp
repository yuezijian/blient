//
// Created by 岳子剑 on 2020/02/12.
//


#ifndef BLIENT__BASE__UTIL__HPP
#define BLIENT__BASE__UTIL__HPP


#include <QLibrary>


class Util
{
public:
    static QLibrary Library( const QString& name )
    {
        /**/  #ifdef __APPLE__
        /**/
        /**/    QString ext = "dylib";
        /**/
        /**/  #elif defined __linux__
        /**/
        /**/    QString ext = "so";
        /**/
        /**/  #elif defined WIN32
        /**/
        /**/    QString ext = "dll";
        /**/
        /**/  #endif

        return QLibrary( QString( "%1.%2" ).arg( name ).arg( ext ) );
    }
};


#endif

//
// Created by 岳子剑 on 2020/03/29.
//


#include "WebEngineUrlSchemeHandlerExecutable.hpp"

#include <QDebug>

#include <QProcess>

#include <QWebEngineUrlRequestJob>


void WebEngineUrlSchemeHandlerExecutable::requestStarted( QWebEngineUrlRequestJob* request )
{
    //qDebug() << request->initiator();
    //qDebug() << request->requestUrl();

    auto url = request->requestUrl().toDisplayString();

    //qDebug() << url;

    if ( url.startsWith( "executable://" ) )
    {
        auto command = url.remove( 0, 13 );

        //qDebug() << command;

        auto i = command.indexOf( "?" );

        auto program = command.left( i );

        auto arguments = command.remove( 0, i + 1 ).split( "&" );

        QProcess::startDetached( program, arguments );
    }
}

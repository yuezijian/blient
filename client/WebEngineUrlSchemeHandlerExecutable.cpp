//
// Created by 岳子剑 on 2020/03/29.
//


#include "WebEngineUrlSchemeHandlerExecutable.hpp"

#include <QDebug>

#include <QDir>
#include <QProcess>

#include <QMessageBox>
#include <QWebEngineUrlRequestJob>


void WebEngineUrlSchemeHandlerExecutable::requestStarted( QWebEngineUrlRequestJob* request )
{
    //qDebug() << request->initiator();
    //qDebug() << request->requestUrl();

    auto url = request->requestUrl().toDisplayString();

    //qDebug() << url;

    if ( url.startsWith( "executable://" ) )
    {
        auto content = url.remove( 0, 13 );

        auto i = content.indexOf( "?" );

        auto program = QDir( content.left( i ) ).absolutePath();

        auto arguments = content.remove( 0, i + 1 ).split( "&" );

        auto command = program;

        for ( auto& arg : arguments )
        {
            command += " ";
            command += arg;
        };

        if ( !QProcess::startDetached( program, arguments ) )
        {
            QMessageBox::warning
                (
                    Q_NULLPTR,
                    QObject::tr( "Warning" ),
                    QString( "Can not execute command:\n%1" ).arg( command )
                );
        }
    }
}

//
// Created by 岳子剑 on 2019/11/01.
//


#include "WebEnginePage.hpp"

#include <QWebChannel>
#include <QWebEngineSettings>

#include "WebEngineChannelObject.hpp"


WebEnginePage::WebEnginePage( QObject* parent ) : QWebEnginePage( parent )
{
    auto channel = new QWebChannel;

    channel->registerObject( "blient", new WebEngineChannelObject( this ) );

    QWebEnginePage::setWebChannel( channel );
}

void WebEnginePage::javaScriptConsoleMessage( QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString& message, int line_number, const QString& source_id )
{
    emit JavaScriptConsoleMessage( level, message, line_number, source_id );
}

//
// Created by 岳子剑 on 2019/11/01.
//


#include "WebEnginePage.hpp"

#include <QWebChannel>
#include <QWebEngineSettings>


WebEnginePage::WebEnginePage( QObject* parent ) : QWebEnginePage( parent )
{
    QWebEnginePage::setWebChannel( new QWebChannel );
}

void WebEnginePage::javaScriptConsoleMessage( QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString& message, int line_number, const QString& source_id )
{
    emit JavaScriptConsoleMessage( level, message, line_number, source_id );
}

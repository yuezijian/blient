//
// Created by 岳子剑 on 2019/11/1.
//

#include "WebEnginePage.hpp"

#include <QWebChannel>

#include "WebEngineChannelObject.hpp"


WebEnginePage::WebEnginePage( QObject* parent ) : QWebEnginePage( parent )
{
    this->object_ = new WebEngineChannelObject;

    auto channel = new QWebChannel;

    channel->registerObject( "editor", this->object_ );

    QWebEnginePage::setWebChannel( channel );
}

void WebEnginePage::ChangeProperty( const QString& value )
{
    this->object_->setProperty( "my_property", value );
}

void WebEnginePage::javaScriptConsoleMessage( QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString& message, int line_number, const QString& source_id )
{
    emit JavaScriptConsoleMessage( level, message, line_number, source_id );
}

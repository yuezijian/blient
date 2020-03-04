//
// Created by 岳子剑 on 2019/03/03.
//


#include "AxWidgetReport.hpp"

#include <QWebEnginePage>
#include <QWebChannel>

#include "AxChannelReport.hpp"


AxWidgetReport::AxWidgetReport() :
    QAxWidget( "{600CD6D9-EBE1-42cb-B8DF-DFB81977122E}" )
{
}

void AxWidgetReport::Attach( QWebEnginePage* page, const QString& name )
{
    auto channel = page->webChannel();

    auto object = new AxChannelReport( this );

    channel->registerObject( name, object );
}

bool AxWidgetReport::translateKeyEvent( int message, int keycode ) const
{
    return QAxWidget::translateKeyEvent( message, keycode );
}

QVariant AxWidgetReport::FileOpenString( const QVariant& value )
{
    auto command = "ExecuteCommand( const QString&, bool, const QString& )";

    return QAxWidget::dynamicCall( command, "FileOpenString", false, value.toString() );
}

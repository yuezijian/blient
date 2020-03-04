//
// Created by 岳子剑 on 2019/03/03.
//


#include "AxWidgetEditor.hpp"

#include <QWebEnginePage>
#include <QWebChannel>

#include "AxChannelEditor.hpp"


AxWidgetEditor::AxWidgetEditor() :
    QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
{
}

void AxWidgetEditor::Attach( QWebEnginePage* page, const QString& name )
{
    auto channel = page->webChannel();

    auto object = new AxChannelEditor( this );

    channel->registerObject( name, object );
}

bool AxWidgetEditor::translateKeyEvent( int message, int keycode ) const
{
    return QAxWidget::translateKeyEvent( message, keycode );
}

QVariant AxWidgetEditor::FileOpenString( const QVariant& value )
{
    auto command = "ExecuteCommand( const QString&, bool, const QString& )";

    return QAxWidget::dynamicCall( command, "FileOpenString", false, value.toString() );
}

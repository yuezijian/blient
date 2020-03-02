//
// Created by 岳子剑 on 2019/03/01.
//


#include "AxWidgetEditor.hpp"

#include <QWebEnginePage>
#include <QWebChannel>

#include "WebEngineChannelObject.hpp"


AxWidgetEditor::AxWidgetEditor() :
    QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
{
}

void AxWidgetEditor::Attach( QWebEnginePage* page, const QString& name )
{
    auto channel = page->webChannel();

    auto object = new WebEngineChannelObject;

    channel->registerObject( name, object );

    auto function = [ = ] ( const QString& content )
    {
        auto command = "ExecuteCommand( const QString&, bool, const QString& )";

        QAxWidget::dynamicCall( command, "FileOpenString", false, content );
    };

    QObject::connect( object, &WebEngineChannelObject::AXC_Editor_FileOpenString, function );
}

bool AxWidgetEditor::translateKeyEvent( int message, int keycode ) const
{
    return QAxWidget::translateKeyEvent( message, keycode );
}

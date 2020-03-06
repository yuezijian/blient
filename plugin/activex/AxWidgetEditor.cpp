//
// Created by 岳子剑 on 2019/03/03.
//


#include "AxWidgetEditor.hpp"


AxWidgetEditor::AxWidgetEditor() :
    QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
{
}

bool AxWidgetEditor::translateKeyEvent( int message, int keycode ) const
{
    return QAxWidget::translateKeyEvent( message, keycode );
}

QVariant AxWidgetEditor::ExecuteCommand( const QString& command, bool ui, const QVariant& value )
{
    auto name = "ExecuteCommand( const QString&, bool, const QString& )";

    return QAxWidget::dynamicCall( name, command, ui, value );
}

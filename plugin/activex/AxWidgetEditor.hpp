//
// Created by 岳子剑 on 2019/02/12.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__AX_WIDGET_EDITOR__HPP
#define BLIENT__PLUGIN__ACTIVEX__AX_WIDGET_EDITOR__HPP


#include <ActiveQt/QAxWidget>


class QWebEnginePage;


class AxWidgetEditor : public QAxWidget
{
    friend class AxChannelEditor;

public:
    AxWidgetEditor();

protected:
    bool translateKeyEvent( int message, int keycode ) const override;

private:
    QVariant ExecuteCommand( const QString& command, bool ui, const QVariant& value );
};


#endif

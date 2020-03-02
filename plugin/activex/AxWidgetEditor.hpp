//
// Created by 岳子剑 on 2019/02/12.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__AX_WIDGET_EDITOR__HPP
#define BLIENT__PLUGIN__ACTIVEX__AX_WIDGET_EDITOR__HPP


#include <ActiveQt/QAxWidget>


class QWebEnginePage;


class AxWidgetEditor : public QAxWidget
{
public:
    AxWidgetEditor();

    void Attach( QWebEnginePage* page, const QString& name );

protected:
    bool translateKeyEvent( int message, int keycode ) const override;
};


#endif

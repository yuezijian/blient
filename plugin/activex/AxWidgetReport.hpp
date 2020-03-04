//
// Created by 岳子剑 on 2020/03/03.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__AX_WIDGET_REPORT__HPP
#define BLIENT__PLUGIN__ACTIVEX__AX_WIDGET_REPORT__HPP


#include <ActiveQt/QAxWidget>


class QWebEnginePage;


class AxWidgetReport : public QAxWidget
{
    friend class AxChannelReport;

public:
    AxWidgetReport();

    void Attach( QWebEnginePage* page, const QString& name );

protected:
    bool translateKeyEvent( int message, int keycode ) const override;

private:
    QVariant FileOpenString( const QVariant& value );
};


#endif

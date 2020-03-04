//
// Created by 岳子剑 on 2020/03/03.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__AX_CHANNEL_REPORT__HPP
#define BLIENT__PLUGIN__ACTIVEX__AX_CHANNEL_REPORT__HPP


#include <QObject>
#include <QVariant>


class AxWidgetReport;


class AxChannelReport : public QObject
{
Q_OBJECT

public:
    explicit AxChannelReport( AxWidgetReport* editor );

public Q_SLOTS:
    QVariant FileOpenString( const QVariant& value );

private:
    AxWidgetReport* report_ = Q_NULLPTR;
};


#endif

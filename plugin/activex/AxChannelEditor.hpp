//
// Created by 岳子剑 on 2020/03/03.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__AX_CHANNEL_EDITOR__HPP
#define BLIENT__PLUGIN__ACTIVEX__AX_CHANNEL_EDITOR__HPP


#include <QObject>
#include <QVariant>


class AxWidgetEditor;


class AxChannelEditor : public QObject
{
Q_OBJECT

public:
    explicit AxChannelEditor( AxWidgetEditor* editor );

public Q_SLOTS:
    QVariant FileOpenString( const QVariant& value );

private:
    AxWidgetEditor* editor_ = Q_NULLPTR;
};


#endif

//
// Created by 岳子剑 on 2019/11/05.
//


#include "WebEngineChannelObject.hpp"

#include <QDebug>


WebEngineChannelObject::WebEngineChannelObject( QObject* parent ) : QObject( parent )
{
}

QVariant WebEngineChannelObject::CreatePlugin( const QVariant& value )
{
    qDebug() << value;

    return QVariant();
}

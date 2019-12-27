//
// Created by 岳子剑 on 2019/11/5.
//

#include "WebEngineChannelObject.hpp"

#include <QDebug>


QVariant WebEngineChannelObject::FileOpenString( const QVariant& value )
{
    qDebug() << value;

    QString content = value.toString();

    return QVariant( "反馈：收到" );
}

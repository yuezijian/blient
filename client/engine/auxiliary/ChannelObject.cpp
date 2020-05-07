//
// Created by 岳子剑 on 2019/11/05.
//


#include "ChannelObject.hpp"

#include <QDebug>


ChannelObject::ChannelObject( QObject* parent ) : QObject( parent )
{
}

QVariant ChannelObject::CreatePlugin( const QVariant& value )
{
    qDebug() << value;

    return QVariant( "hi" );
}

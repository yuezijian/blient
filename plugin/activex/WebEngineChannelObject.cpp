//
// Created by 岳子剑 on 2019/11/5.
//

#include "WebEngineChannelObject.hpp"


QVariant WebEngineChannelObject::FileOpenString( const QVariant& value )
{
    emit AXC_Editor_FileOpenString( value.toString() );

    return QVariant( true );
}

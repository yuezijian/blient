//
// Created by 岳子剑 on 2019/11/5.
//

#include "WebEngineChannelObject.hpp"


QVariant WebEngineChannelObject::FileOpenString( const QVariant& value )
{
    return emit JS_FileOpenString( value.toString() );
}

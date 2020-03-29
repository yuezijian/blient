//
// Created by 岳子剑 on 2019/11/05.
//


#include "WebEngineChannelObject.hpp"

#include "AxWidget.hpp"


WebEngineChannelObject::WebEngineChannelObject( AxWidget* widget ) : widget_( widget )
{
}

QVariant WebEngineChannelObject::FileOpenString( const QVariant& value )
{
    this->widget_->Test();

    return QVariant();
}

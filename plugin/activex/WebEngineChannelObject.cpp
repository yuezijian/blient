//
// Created by 岳子剑 on 2019/11/5.
//


#include "WebEngineChannelObject.hpp"

#include "AxWidgetEditor.hpp"


WebEngineChannelObject::WebEngineChannelObject( AxWidgetEditor* editor ) : editor_( editor )
{
}

QVariant WebEngineChannelObject::FileOpenString( const QVariant& value )
{
    return this->editor_->FileOpenString( value.toString() );
}

//
// Created by 岳子剑 on 2020/03/03.
//


#include "AxChannelEditor.hpp"

#include "AxWidgetEditor.hpp"


AxChannelEditor::AxChannelEditor( AxWidgetEditor* editor ) : editor_( editor )
{
}

QVariant AxChannelEditor::FileOpenString( const QVariant& value )
{
    return this->editor_->FileOpenString( value.toString() );
}

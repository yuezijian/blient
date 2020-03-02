//
// Created by 岳子剑 on 2019/12/30.
//


#include <QtWidgets/QtWidgets>

#ifdef WIN32
#include "AxWidgetEditor.hpp"
#else
#include "AxWidget.hpp"
#endif


extern "C" Q_DECL_EXPORT QWidget* CreateWidget( QWebEnginePage* page, const QString& name )
{
    #ifdef WIN32

    auto ax_widget = new AxWidgetEditor;

    if ( ax_widget->isNull() )
    {
        auto label = new QLabel;

        label->setAlignment( Qt::AlignCenter );
        label->setMargin( 20 );
        label->setText( QString( QObject::tr( "Plugin [ %1 ] not found" ) ).arg( name ) );

        return label;
    }

    ax_widget->Attach( page, name );

    return ax_widget;

    #else

    auto ax_widget = new AxWidget;

    auto channel = new QWebChannel;

    channel->registerObject( name, ax_widget->ChannelObject() );

    page->setWebChannel( channel );

    return ax_widget;

    //auto label = new QLabel;
    //
    //label->setAlignment( Qt::AlignCenter );
    //label->setMargin( 20 );
    //label->setText( "Windows ActiveX Control" );
    //
    //return label;

    #endif
}

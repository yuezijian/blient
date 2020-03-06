//
// Created by 岳子剑 on 2019/12/30.
//


#include <QtWidgets/QtWidgets>

#include <QWebChannel>
#include <QWebEnginePage>

#ifdef WIN32
#include "AxChannelEditor.hpp"
#include "AxChannelReport.hpp"
#include "AxWidgetEditor.hpp"
#include "AxWidgetReport.hpp"
#else
#include "AxWidget.hpp"
#endif


QWidget* CreateWidget( QAxWidget* widget, QObject* object, QWebEnginePage* page, const QString& name )
{
    #ifdef WIN32

    if ( widget->isNull() )
    {
        auto label = new QLabel;

        label->setAlignment( Qt::AlignCenter );
        label->setMargin( 20 );
        label->setText( QString( QObject::tr( "Plugin [ %1 ] not found" ) ).arg( name ) );

        return label;
    }

    page->webChannel()->registerObject( name, object );

    return widget;

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

extern "C" Q_DECL_EXPORT QWidget* CreateWidgetEditor( QWebEnginePage* page, const QString& name )
{
    auto widget  = new AxWidgetEditor;
    auto channel = new AxChannelEditor( widget );

    return CreateWidget( widget, channel, page, name );
}

extern "C" Q_DECL_EXPORT QWidget* CreateWidgetReport( QWebEnginePage* page, const QString& name )
{
    auto widget  = new AxWidgetReport;
    auto channel = new AxChannelReport( widget );

    return CreateWidget( widget, channel, page, name );
}

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

#ifdef WIN32

QWidget* CreateWidget( QAxWidget* widget, QObject* object, QWebEnginePage* page, const QString& name )
{
    if ( widget->isNull() )
    {
        auto label = new QLabel;

        label->setAlignment( Qt::AlignCenter );
        label->setMargin( 20 );
        label->setText( QString( QString::fromLocal8Bit( "插件 [ %1 ] 未找到" ) ).arg( name ) );

        return label;
    }

    page->webChannel()->registerObject( name, object );

    return widget;
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

#else

QWidget* CreateWidget( QWebEnginePage* page, const QString& name )
{
    //auto ax_widget = new AxWidget;
    //
    //auto channel = new QWebChannel;
    //
    //channel->registerObject( name, ax_widget->ChannelObject() );
    //
    //page->setWebChannel( channel );
    //
    //return ax_widget;

    auto label = new QLabel;

    label->setAlignment( Qt::AlignCenter );
    label->setMargin( 20 );
    label->setText( QString( "Windows ActiveX Control %1" ).arg( name ) );

    return label;
}

extern "C" Q_DECL_EXPORT QWidget* CreateWidgetEditor( QWebEnginePage* page, const QString& name )
{
    return CreateWidget( page, name );
}

extern "C" Q_DECL_EXPORT QWidget* CreateWidgetReport( QWebEnginePage* page, const QString& name )
{
    return CreateWidget( page, name );
}

#endif


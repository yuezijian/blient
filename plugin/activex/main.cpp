//
// Created by 岳子剑 on 2019/12/30.
//


#include <QDebug>

#include <QtWidgets/QtWidgets>

//#include <QWebEnginePage>
//#include <QWebChannel>

#include "WebEngineChannelObject.hpp"

#include "AxWidget.hpp"


#ifdef WIN32

#include <ActiveQt/QAxWidget>

class AxWidgetEditor : public QAxWidget
{
public:
    AxWidgetEditor() : QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
    {
    }

protected:
    //bool translateKeyEvent( int message, int keycode ) const override
    //{
    //    return QAxWidget::translateKeyEvent( message, keycode );
    //}
};

#endif




extern "C" Q_DECL_EXPORT QWidget* CreateWidget( QWebEnginePage* page, const QString& name )
{
    #ifdef WIN32

    auto ax_widget = new AxWidgetEditor;

    if ( !ax_widget->isNull() )
    {
        auto channel = new QWebChannel;

        auto object = new WebEngineChannelObject;

        channel->registerObject( name, object );

        page->setWebChannel( channel );

        QObject::connect
        (
            object, &WebEngineChannelObject::AXC_Editor_FileOpenString,
            [ = ] ( const QString& content )
            {
                auto function = "ExecuteCommand( const QString&, bool, const QString& )";

                ax_widget->dynamicCall( function, "FileOpenString", false, content );
            }
        );
    }

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

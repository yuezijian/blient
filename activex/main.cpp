//
// Created by 岳子剑 on 2019/12/30.
//


#include <QtWidgets/QtWidgets>

#include <QWebEnginePage>
#include <QWebChannel>

#include "WebEngineChannelObject.hpp"

#ifdef _WIN32

#include <ActiveQt/QAxWidget>


class AxWidgetEditor : public QAxWidget
{
public:
    AxWidgetEditor() : QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
    {
    }

protected:
    //void mousePressEvent( QMouseEvent* event ) override
    //{
    //    qDebug() << "Mouse Pressed";

    //    QAxWidget::setFocus();
    //    QAxWidget::clearFocus();
    //    QAxWidget::mousePressEvent( event );
    //}

private:
    ;
};

#endif



extern "C" Q_DECL_EXPORT QWidget* CreateWidgetAX( QWebEnginePage* page, const QString& name )
{
    #ifdef _WIN32

    auto channel = new QWebChannel;

    auto object = new WebEngineChannelObject;

    channel->registerObject( name, object );

    page->setWebChannel( channel );

    auto ax_widget = new AxWidgetEditor;

    if ( !ax_widget->isNull() )
    {
        QObject::connect
        (
            object, &WebEngineChannelObject::AXC_Editor_FileOpenString,
            [ = ] ( const QString& content )
            {
                auto function = "ExecuteCommand( const QString&, bool, const QString& )";

                ax_widget->dynamicCall( function, "FileOpenString", false, content );
            }
        );

        return ax_widget;
    }

    #endif

    return Q_NULLPTR;
}

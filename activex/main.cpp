//
// Created by 岳子剑 on 2019/12/30.
//


#include <QtWidgets/QtWidgets>

#include <ActiveQt/QAxWidget>

#include <QWebEnginePage>
#include <QWebChannel>

#include "WebEngineChannelObject.hpp"


class AxWidgetEditor : public QAxWidget
{
public:
    AxWidgetEditor() : QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
    {
    }

protected:
    //void focusInEvent( QFocusEvent* event ) override
    //{
    //    qDebug() << "focus in";

    //    QAxWidget::focusInEvent( event );
    //}

    //void focusOutEvent( QFocusEvent* event ) override
    //{
    //    qDebug() << "focus out";

    //    QAxWidget::focusOutEvent( event );
    //}

    //void resizeEvent( QResizeEvent* event ) override
    //{
    //    qDebug() << "axw resize";

    //    //QAxWidget::setFocus();
    //    //QAxWidget::clearFocus();

    //    //QAxWidget::resizeEvent( event );

    //    QAxWidget::update();
    //}

    //bool translateKeyEvent( int message, int keycode ) const override
    //{
    //    return QAxWidget::translateKeyEvent( message, keycode );
    //}

    //void mousePressEvent( QMouseEvent* event ) override
    //{
    //    qDebug() << "Mouse Pressed";

    //    //QAxWidget::setFocus();

    //    //QAxWidget::clearFocus();
    //    QAxWidget::update();
    //    QAxWidget::mousePressEvent( event );

    //    //QAxWidget::setFocus();
    //    //QAxWidget::update();
    //}

private:
    ;
};


extern "C" Q_DECL_EXPORT QWidget* CreateWidget( QWebEnginePage* page, const QString& name )
{
    auto ax_widget = new AxWidgetEditor;

    //if ( !ax_widget->isNull() )
    //{
    //    auto channel = new QWebChannel;

    //    auto object = new WebEngineChannelObject;

    //    channel->registerObject( name, object );

    //    page->setWebChannel( channel );

    //    QObject::connect
    //    (
    //        object, &WebEngineChannelObject::AXC_Editor_FileOpenString,
    //        [ = ] ( const QString& content )
    //    {
    //        auto function = "ExecuteCommand( const QString&, bool, const QString& )";

    //        ax_widget->dynamicCall( function, "FileOpenString", false, content );
    //    }
    //    );

    //    return ax_widget;
    //}

    return ax_widget;
}

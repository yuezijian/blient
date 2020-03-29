//
// Created by 岳子剑 on 2019/09/25.
//


#include "WebEngineView.hpp"

#include <QEvent>

#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

#include "Client.hpp"
#include "MainWindow.hpp"
#include "TabWidget.hpp"
#include "WebEnginePage.hpp"
#include "WebEngineViewPopup.hpp"


WebEngineView::WebEngineView()
{
    QObject::connect
        (
            this, &QWebEngineView::loadStarted, [ this ]()
            {
                this->load_progress_ = 0;
            }
        );

    QObject::connect
        (
            this, &QWebEngineView::loadProgress, [ this ]( int progress )
            {
                this->load_progress_ = progress;
            }
        );

    QObject::connect
        (
            this, &QWebEngineView::loadFinished, [ this ]( bool success )
            {
                this->load_progress_ = success ? 100 : -1;
            }
        );
}

//bool WebEngineView::event( QEvent* event )
//{
//    if ( event->type() == QEvent::ChildAdded )
//    {
//        auto ce = dynamic_cast< QChildEvent* >( event );
//
//        if ( ce )
//        {
//            auto child = ce->child();
//
//            auto widget = qobject_cast< QWidget* >( child );
//
//            if ( widget )
//            {
//                widget->installEventFilter( this );
//            }
//        }
//    }
//
//    return QWebEngineView::event( event );
//}
//
//bool WebEngineView::eventFilter( QObject* object, QEvent* event )
//{
//    if ( event->type() == QEvent::FocusIn )
//    {
//        QWebEngineView::update();
//    }
//
//    return QWebEngineView::eventFilter( object, event );
//}

QWebEngineView* WebEngineView::createWindow( QWebEnginePage::WebWindowType type )
{
    auto window = qobject_cast< MainWindow* >( WebEngineView::window() );

    if ( window )
    {
        switch ( type )
        {
            case QWebEnginePage::WebBrowserWindow:
            {
                return window->ClientInstance()->CreateWindow()->Tab()->View();
            }
            case QWebEnginePage::WebBrowserTab:
            {
                return window->Tab()->CreateView();
            }
            case QWebEnginePage::WebDialog:
            {
                auto popup = new WebEngineViewPopup;

                popup->show();

                return popup->View();
            }
            case QWebEnginePage::WebBrowserBackgroundTab:
            {
                return window->Tab()->CreateViewBackground();
            }
            default:
                ;
        }
    }

    return QWebEngineView::createWindow( type );
}

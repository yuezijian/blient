//
// Created by 岳子剑 on 2019/9/25.
//


#include "WebEngineView.hpp"

#include "MainWindow.hpp"
#include "WebEnginePage.hpp"

#include <QEvent>

#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>


WebEngineView::WebEngineView()
{
    //this->page_ = new WebEnginePage;

    //QWebEngineView::setPage( this->page_ );
}

WebEngineView::~WebEngineView()
{
    //delete this->page_;

    //this->page_ = Q_NULLPTR;
}

bool WebEngineView::event( QEvent* event )
{
    if ( event->type() == QEvent::ChildAdded )
    {
        auto ce = dynamic_cast< QChildEvent* >( event );

        if ( ce )
        {
            auto child = ce->child();

            auto widget = qobject_cast< QWidget* >( child );

            if ( widget )
            {
                widget->installEventFilter( this );
            }
        }
    }

    return QWebEngineView::event( event );
}

bool WebEngineView::eventFilter( QObject* object, QEvent* event )
{
    if ( event->type() == QEvent::FocusIn )
    {
        QWebEngineView::update();
    }

    return QWebEngineView::eventFilter( object, event );
}

QWebEngineView* WebEngineView::createWindow( QWebEnginePage::WebWindowType type )
{
    auto window = qobject_cast< MainWindow* >( WebEngineView::window() );

    if ( window )
    {
        //switch ( type )
        //{
        //    case QWebEnginePage::WebBrowserWindow:
        //        break;
        //    case QWebEnginePage::WebBrowserTab:
        //        break;
        //    case QWebEnginePage::WebDialog:
        //        break;
        //    default:
        //        ;
        //}
    }

    //return QWebEngineView::createWindow( type );

    //qDebug() << view;
    //qDebug() << this->Page();

    return QWebEngineView::createWindow( type );
}

//
// Created by 岳子剑 on 2019/9/25.
//


#include "WebEngineView.hpp"

#include "WebEnginePage.hpp"

#include <QEvent>

#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>


WebEngineView::WebEngineView()
{
    this->page_ = new WebEnginePage;

    QWebEngineView::setPage( this->page_ );
}

WebEngineView::~WebEngineView()
{
    delete this->page_;

    this->page_ = Q_NULLPTR;
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

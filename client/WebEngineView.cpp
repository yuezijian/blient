//
// Created by 岳子剑 on 2019/9/25.
//

#include <QEvent>
#include "WebEngineView.hpp"


bool WebEngineView::event( QEvent* event )
{
    if ( event->type() == QEvent::ChildAdded )
    {
        auto ce = dynamic_cast< QChildEvent* >( event );

        if ( ce )
        {
            ce->child()->installEventFilter( this );
        }
    }
    else if ( event->type() == QEvent::ChildRemoved )
    {
        auto ce = dynamic_cast< QChildEvent* >( event );

        if ( ce )
        {
            ce->child()->removeEventFilter( this );
        }
    }

    return QWebEngineView::event( event );
}

bool WebEngineView::eventFilter( QObject* object, QEvent* event )
{
    if ( event->type() == QEvent::MouseButtonPress )
    {
        qDebug() << object;
        qDebug() << event;
    }

    return QWebEngineView::eventFilter( object, event );
}

//
// Created by 岳子剑 on 2020/3/11.
//


#include "TabWidget.hpp"

#include <QTabBar>

#include "WebEnginePage.hpp"
#include "WebEngineView.hpp"


TabWidget::TabWidget()
{
    auto bar = QTabWidget::tabBar();

    bar->setContextMenuPolicy( Qt::CustomContextMenu );
    bar->setSelectionBehaviorOnRemove( QTabBar::SelectPreviousTab );
    bar->setMovable( true );
    bar->setTabsClosable( true );

    //QTabWidget::setDocumentMode( true );
    QTabWidget::setElideMode( Qt::ElideRight );
}

WebEngineView* TabWidget::ActiveView() const
{
    return qobject_cast< WebEngineView* >( QTabWidget::currentWidget() );
}

WebEngineView* TabWidget::CreateTab()
{
    auto view = new WebEngineView;
    //auto page = new WebEnginePage;

    QObject::connect
        (
            view, &QWebEngineView::urlChanged, [ = ]( const QUrl &url )
            {
                auto index = QTabWidget::indexOf( view );

                if ( index != -1 )
                {
                    QTabWidget::tabBar()->setTabData( index, url );
                }

                if ( currentIndex() == index )
                {
                    emit ChangeURL(url);
                }
            }
        );

    //view->setPage( page );
    view->show();

    QTabWidget::addTab( view, QObject::tr( "Empty" ) );

    return view;
}

void TabWidget::SetURL( const QUrl& url )
{
    if ( auto view = this->ActiveView() )
    {
        view->setUrl( url );
        view->setFocus();
    }
}

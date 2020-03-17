//
// Created by 岳子剑 on 2020/3/11.
//


#include "TabWidget.hpp"

#include <QTabBar>

#include "WebEnginePage.hpp"
#include "WebEngineView.hpp"


TabWidget::TabWidget()
{
    auto tab = QTabWidget::tabBar();

    tab->setContextMenuPolicy( Qt::CustomContextMenu );
    tab->setSelectionBehaviorOnRemove( QTabBar::SelectPreviousTab );
    tab->setMovable( true );
    tab->setTabsClosable( true );

    //QTabWidget::setDocumentMode( true );
    QTabWidget::setElideMode( Qt::ElideRight );

    QObject::connect
        (
            tab, &QTabBar::tabBarDoubleClicked, [ this ]( int index )
            {
                qDebug() << "hello";

                if ( index == -1 )
                {
                    this->CreateView();
                }
            }
        );

    QObject::connect( tab, &QTabBar::tabCloseRequested, this, &TabWidget::CloseTab );
}

WebEngineView* TabWidget::View() const
{
    return qobject_cast< WebEngineView* >( QTabWidget::currentWidget() );
}

void TabWidget::CloseTab( int index )
{
    if ( auto view = qobject_cast< WebEngineView* >( QTabWidget::widget( index ) ) )
    {
        auto focus = view->hasFocus();

        QTabWidget::removeTab( index );

        auto count = QTabWidget::count();

        if ( focus && count > 0 )
        {
            this->View()->setFocus();
        }

        if ( count == 0 )
        {
            this->CreateView();
        }

        view->deleteLater();
    }
}

WebEngineView* TabWidget::CreateView()
{
    auto view = this->CreateViewBackground();

    QTabWidget::setCurrentWidget( view );

    return view;
}

WebEngineView* TabWidget::CreateViewBackground()
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

                if ( QTabWidget::currentIndex() == index )
                {
                    emit ChangeURL(url);
                }
            }
        );

    QObject::connect
        (
            view, &QWebEngineView::titleChanged, [ = ]( const QString& title )
            {
                int index = QTabWidget::indexOf( view );

                if ( index != -1 )
                {
                    QTabWidget::setTabText( index, title );
                    QTabWidget::setTabToolTip( index, title );
                }

                if ( QTabWidget::currentIndex() == index )
                {
                    emit ChangeTitle( title );
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
    if ( auto view = this->View() )
    {
        view->setUrl( url );
        view->setFocus();
    }
}

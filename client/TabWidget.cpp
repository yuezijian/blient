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

    QTabWidget::setDocumentMode( true );
    QTabWidget::setElideMode( Qt::ElideRight );

    QObject::connect
        (
            tab, &QTabBar::tabBarDoubleClicked, [ this ]( int index )
            {
                if ( index == -1 )
                {
                    this->CreateView();
                }
            }
        );

    QObject::connect( tab, &QTabBar::tabCloseRequested, this, &TabWidget::CloseTab );

    QObject::connect( this, &QTabWidget::currentChanged, this, &TabWidget::ChangeCurrent );
}

WebEngineView* TabWidget::View() const
{
    return qobject_cast< WebEngineView* >( QTabWidget::currentWidget() );
}

WebEngineView* TabWidget::View( int index ) const
{
    return qobject_cast< WebEngineView* >( QTabWidget::widget( index ) );
}

void TabWidget::CloseTab( int index )
{
    if ( auto view = this->View( index ) )
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
    auto page = new WebEnginePage( view );

    view->setPage( page );

    QObject::connect
        (
            view, &QWebEngineView::urlChanged, [ this, view ]( const QUrl &url )
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
            view, &QWebEngineView::titleChanged, [ this, view ]( const QString& title )
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

    QObject::connect
        (
            view, &QWebEngineView::loadProgress, [ this, view ]( int progress )
            {
                if ( QTabWidget::currentIndex() == QTabWidget::indexOf( view ) )
                {
                    emit LoadProgress( progress );
                }
            }
        );

    //QObject::connect( view, &QObject::destroyed, [ view ]() { view->page()->deleteLater(); } );

    view->show();

    QTabWidget::addTab( view, QObject::tr( "Empty" ) );

    return view;
}

void TabWidget::SetURL( const QString& url )
{
    if ( auto view = this->View() )
    {
        view->setUrl( QUrl::fromUserInput( url ) );
        view->setFocus();
    }
}

void TabWidget::ChangeCurrent( int index )
{
    if ( index != -1 )
    {
        auto view = this->View( index );

        if ( !view->url().isEmpty() )
        {
            view->setFocus();
        }

        emit ChangeURL( view->url() );
        emit ChangeTitle( view->title() );
        emit LoadProgress( view->LoadProgress() );
    }
    else
    {
        emit ChangeURL(QUrl());
        emit ChangeTitle(QString());
        emit LoadProgress( 0 );
    }
}

void TabWidget::TriggerWebAction( QWebEnginePage::WebAction action )
{
    if ( auto view = this->View() )
    {
        view->triggerPageAction( action );
        view->setFocus();
    }
}

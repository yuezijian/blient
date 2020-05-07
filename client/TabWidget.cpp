//
// Created by 岳子剑 on 2020/03/11.
//


#include "TabWidget.hpp"

#include <QTabBar>
#include <QWebChannel>

#include "engine/WebEnginePage.hpp"
#include "engine/WebEngineView.hpp"

#include "WebWidget.hpp"


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
                    this->CreateWidgetActive();
                }
            }
        );

    QObject::connect( tab, &QTabBar::tabCloseRequested, this, &TabWidget::CloseWidget );

    QObject::connect( this, &QTabWidget::currentChanged, this, &TabWidget::ChangeCurrent );
}

WebWidget* TabWidget::ActiveWidget() const
{
    return qobject_cast< WebWidget* >( QTabWidget::currentWidget() );
}

WebWidget* TabWidget::Widget( int index ) const
{
    return qobject_cast< WebWidget* >( QTabWidget::widget( index ) );
}

WebWidget* TabWidget::CreateWidget()
{
    auto widget = new WebWidget;

    auto view = widget->View();

    QObject::connect
        (
            view, &QWebEngineView::urlChanged, [ this, widget ]( const QUrl& url )
            {
                auto index = QTabWidget::indexOf( widget );

                if ( index != -1 )
                {
                    QTabWidget::tabBar()->setTabData( index, url );
                }

                if ( QTabWidget::currentIndex() == index )
                {
                    emit ChangeURL( url );
                }
            }
        );

    QObject::connect
        (
            view, &QWebEngineView::titleChanged, [ this, widget ]( const QString& title )
            {
                int index = QTabWidget::indexOf( widget );

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
            view, &QWebEngineView::loadProgress, [ this, widget ]( int progress )
            {
                if ( QTabWidget::currentIndex() == QTabWidget::indexOf( widget ) )
                {
                    emit LoadProgress( progress );
                }
            }
        );

    widget->show();

    QTabWidget::addTab( widget, QString::fromLocal8Bit( "新页面" ) );

    return widget;
}

WebWidget* TabWidget::CreateWidgetActive()
{
    auto widget = this->CreateWidget();

    QTabWidget::setCurrentWidget( widget );

    return widget;
}

void TabWidget::CloseWidgetActive()
{
    if ( auto widget = this->ActiveWidget() )
    {
        auto focus = widget->hasFocus();

        QTabWidget::removeTab( QTabWidget::indexOf( widget ) );

        auto count = QTabWidget::count();

        if ( focus && count > 0 )
        {
            this->ActiveWidget()->setFocus();
        }

        if ( count == 0 )
        {
            this->CreateWidgetActive();
        }

        widget->deleteLater();
    }
}

void TabWidget::CloseWidget( int index )
{
    if ( auto widget = this->Widget( index ) )
    {
        auto focus = widget->hasFocus();

        QTabWidget::removeTab( index );

        auto count = QTabWidget::count();

        if ( focus && count > 0 )
        {
            this->ActiveWidget()->setFocus();
        }

        if ( count == 0 )
        {
            this->CreateWidgetActive();
        }

        widget->deleteLater();
    }
}

void TabWidget::SetURL( const QString& url )
{
    if ( auto widget = this->ActiveWidget() )
    {
        widget->View()->setUrl( QUrl::fromUserInput( url ) );
        widget->setFocus();
    }
}

void TabWidget::ChangeCurrent( int index )
{
    if ( index != -1 )
    {
        auto widget = this->Widget( index );
        auto view   = widget->View();

        if ( !view->url().isEmpty() )
        {
            widget->setFocus();
        }

        emit ChangeURL( view->url() );
        emit ChangeTitle( view->title() );
        emit LoadProgress( view->LoadProgress() );
    }
    else
    {
        emit ChangeURL( QUrl() );
        emit ChangeTitle( QString() );
        emit LoadProgress( 0 );
    }
}

void TabWidget::TriggerWebAction( QWebEnginePage::WebAction action )
{
    if ( auto widget = this->ActiveWidget() )
    {
        widget->View()->triggerPageAction( action );
        widget->setFocus();
    }
}

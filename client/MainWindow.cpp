//
// Created by 岳子剑 on 2019/9/27.
//


#include "../base/Util.hpp"

#include "MainWindow.hpp"

#include <QWebEngineHistory>
#include <QWebEngineHistoryItem>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

#include "TabWidget.hpp"
#include "WebEngineConsole.hpp"
#include "WebEnginePage.hpp"
#include "WebEngineView.hpp"


MainWindow::MainWindow( Client* client, QWebEngineProfile* profile ) : client_( client )
{
    this->SetupUI();

    //this->ToURL( "localhost:3000" );
    //this->ToURL( "192.168.1.7:3000" );
}

//void MainWindow::InstallPlugin()
//{
//    //auto library = Util::Library( "activex" );
//    //
//    //if ( library.load() )
//    //{
//    //    typedef QWidget* ( *Function )( QWebEnginePage*, const QString& );
//    //
//    //    {
//    //        auto CreateWidget = ( Function )( library.resolve( "CreateWidgetEditor" ) );
//    //
//    //        if ( CreateWidget )
//    //        {
//    //            QWidget* widget = CreateWidget( this->view_->page(), "editor" );
//    //
//    //            if ( widget )
//    //            {
//    //                this->AddAssistWidget( "Editor", widget );
//    //            }
//    //        }
//    //    }
//    //    {
//    //        auto CreateWidget = ( Function )( library.resolve( "CreateWidgetReport" ) );
//    //
//    //        if ( CreateWidget )
//    //        {
//    //            QWidget* widget = CreateWidget( this->view_->page(), "report" );
//    //
//    //            if ( widget )
//    //            {
//    //                this->AddAssistWidget( "Report", widget );
//    //            }
//    //        }
//    //    }
//    //
//    //    return;
//    //}
//    //
//    //QMessageBox::warning( this, QObject::tr( "Warning" ), library.errorString() );
//}

void MainWindow::SetupUI()
{
    this->tool_ = new QToolBar();

    this->tool_->setFloatable( false );
    this->tool_->setMovable( false );

    auto nav_back    = new QAction( QObject::tr( "Back"    ) );
    auto nav_forward = new QAction( QObject::tr( "Forward" ) );
    auto nav_reload  = new QAction( QObject::tr( "Refresh" ) );

    //nav_back->setDisabled( true );
    //nav_forward->setDisabled( true );

    this->edit_ = new QLineEdit;

    auto new_tab  = new QAction( QObject::tr( "+" ) );

    this->tool_->addAction( nav_back );
    this->tool_->addAction( nav_forward );
    this->tool_->addAction( nav_reload );

    this->tool_->addWidget( this->edit_ );

    this->tool_->addAction( new_tab );

    QMainWindow::addToolBar( Qt::TopToolBarArea, this->tool_ );

    auto widget = new QWidget;
    auto layout = new QVBoxLayout;

    this->tab_  = new TabWidget;

    widget->setLayout( layout );

    layout->addWidget( this->tab_ );

    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    QMainWindow::setCentralWidget( widget );

    //QObject::connect
    //    (
    //        nav_back, &QAction::triggered,
    //        [ = ]()
    //        {
    //            this->view_->back();
    //
    //            auto history = this->view_->history();
    //            auto url     = history->currentItem().url();
    //
    //            this->address_->setText( url.toDisplayString() );
    //        }
    //    );

    //QObject::connect
    //    (
    //        nav_forward, &QAction::triggered,
    //        [ = ]()
    //        {
    //            this->view_->forward();
    //
    //            auto history = this->view_->history();
    //            auto url     = history->currentItem().url();
    //
    //            this->address_->setText( url.toDisplayString() );
    //        }
    //    );

    //QObject::connect
    //    (
    //        nav_reload, &QAction::triggered,
    //        [ = ]()
    //        {
    //            this->view_->reload();
    //
    //            auto url = this->view_->history()->currentItem().url();
    //
    //            this->address_->setText( url.toDisplayString() );
    //        }
    //    );

    QObject::connect
        (
            new_tab, &QAction::triggered, [ this ]()
            {
                this->tab_->CreateView();
            }
        );

    //auto status = QMainWindow::statusBar();

    //status->showMessage( QObject::tr( "Ready" ) );

    QMainWindow::setMinimumSize( QSize( 800, 500 ) );

    QObject::connect
        (
            this->edit_, &QLineEdit::returnPressed, [ = ]()
            {
                this->tab_->SetURL( QUrl::fromUserInput( this->edit_->text() ) );
            }
        );

    QObject::connect
        (
            this->tab_, &TabWidget::ChangeURL, [ = ]( const QUrl& url )
            {
                this->edit_->setText( url.toDisplayString() );
            }
        );

    //QObject::connect
    //    (
    //        this->view_, &QWebEngineView::loadStarted,
    //        [ = ] ()
    //        {
    //            auto history = this->view_->history();
    //
    //            nav_back->setDisabled( history->backItem().url().isEmpty() );
    //            nav_forward->setDisabled( history->forwardItem().url().isEmpty() );
    //        }
    //    );

    //auto console = new WebEngineConsole( this->view_ );
    //
    //this->AddAssistWidget( QObject::tr( "Console" ), console );

    this->tab_->CreateView();
}

void MainWindow::AddAssistWidget( const QString& title, QWidget* widget, int width )
{
    //widget->show();

    //widget->setMinimumWidth( 850 );

    auto dock = new QDockWidget( title );

    dock->setWidget( widget );

    QMainWindow::addDockWidget( Qt::RightDockWidgetArea, dock );

    this->tool_->addAction( dock->toggleViewAction() );
}

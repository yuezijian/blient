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
    this->tool_->toggleViewAction()->setEnabled( false );

    this->nav_back_    = new QAction( QObject::tr( "Back"    ) );
    this->nav_forward_ = new QAction( QObject::tr( "Forward" ) );
    this->nav_reload_  = new QAction( QObject::tr( "Reload"  ) );

    this->edit_ = new QLineEdit;

    this->tool_->addAction( this->nav_back_    );
    this->tool_->addAction( this->nav_forward_ );
    this->tool_->addAction( this->nav_reload_  );

    this->tool_->addWidget( this->edit_ );

    QMainWindow::addToolBar( Qt::TopToolBarArea, this->tool_ );

    auto widget = new QWidget;
    auto layout = new QVBoxLayout;

    this->tab_  = new TabWidget;

    widget->setLayout( layout );

    layout->addWidget( this->tab_ );

    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    QMainWindow::setCentralWidget( widget );

    auto status = QMainWindow::statusBar();

    this->progress_ = new QProgressBar;

    this->progress_->setRange( 0, 100 );

    status->addWidget( this->progress_ );

    QMainWindow::setMinimumSize( QSize( 800, 500 ) );

    QObject::connect
        (
            this->nav_back_, &QAction::triggered, [ this ]()
            {
                this->tab_->TriggerWebAction( QWebEnginePage::Back );
            }
        );

    QObject::connect
        (
            this->nav_forward_, &QAction::triggered, [ this ]()
            {
                this->tab_->TriggerWebAction( QWebEnginePage::Forward );
            }
        );

    QObject::connect
        (
            this->nav_reload_, &QAction::triggered, [ this ]()
            {
                this->tab_->TriggerWebAction( QWebEnginePage::WebAction( this->nav_reload_->data().toInt() ) );
            }
        );

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

    QObject::connect( this->tab_, &TabWidget::ChangeTitle, this, &MainWindow::ChangeTitle );

    QObject::connect( this->tab_, &TabWidget::LoadProgress, this, &MainWindow::LoadProgress );

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

void MainWindow::ChangeTitle( const QString& title )
{
    if ( title.isEmpty() )
    {
        QMainWindow::setWindowTitle( QString() );
    }
    else
    {
        QMainWindow::setWindowTitle( title );
    }
}

void MainWindow::LoadProgress( int progress )
{
    if ( 0 < progress && progress < 100 )
    {
        this->nav_reload_->setText( QObject::tr( "Stop"  ) );
        this->nav_reload_->setData( QWebEnginePage::Stop );

        if ( this->progress_->isHidden() )
        {
            this->progress_->show();
        }

        this->progress_->setValue( progress );
    }
    else
    {
        this->nav_reload_->setText( QObject::tr( "Reload"  ) );
        this->nav_reload_->setData( QWebEnginePage::Reload );

        this->progress_->hide();
        this->progress_->setValue( 0 );
    }
}

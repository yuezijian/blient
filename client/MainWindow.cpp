//
// Created by 岳子剑 on 2019/9/27.
//


#include "../base/Util.hpp"

#include "MainWindow.hpp"

#include <QWebChannel>

#include "WebEngineConsole.hpp"
#include "WebEnginePage.hpp"
#include "WebEngineView.hpp"


MainWindow::MainWindow()
{
    this->SetupUI();

    this->ToURL( "localhost:3000" );
}

void MainWindow::InstallPlugin()
{
    auto library = Util::Library( "activex" );

    if ( library.load() )
    {
        typedef QWidget* ( *Function )( QWebEnginePage*, const QString& );

        auto CreateWidget = ( Function )( library.resolve( "CreateWidget" ) );

        if ( CreateWidget )
        {
            QWidget* widget = CreateWidget( this->view_->page(), "editor" );

            if ( widget )
            {
                this->AddAssistWidget( "ActiveX", widget );

                return;
            }
        }
    }

    QMessageBox::warning( this, QObject::tr( "Error" ), library.errorString() );
}

void MainWindow::ToURL( const QString& address )
{
    if ( address.indexOf( "http://" ) == 0 || address.indexOf( "https://" ) == 0 )
    {
        this->view_->setUrl( address );
    }
    else
    {
        this->view_->setUrl( QString( "http://%1" ).arg( address ) );
    }

    this->address_->setText( this->view_->url().toDisplayString() );
}

void MainWindow::SetupUI()
{
    this->toolbar_ = new QToolBar();

    this->toolbar_->setFloatable( false );
    this->toolbar_->setMovable( false );

    auto nav_back    = new QAction( QObject::tr( "Back"    ) );
    auto nav_forward = new QAction( QObject::tr( "Forward" ) );
    auto nav_refresh = new QAction( QObject::tr( "Refresh" ) );

    this->address_ = new QLineEdit;

    this->toolbar_->addAction( nav_back );
    this->toolbar_->addAction( nav_forward );
    this->toolbar_->addAction( nav_refresh );

    this->toolbar_->addWidget( this->address_ );

    QMainWindow::addToolBar( Qt::TopToolBarArea, this->toolbar_ );

    this->view_ = new WebEngineView;

    QMainWindow::setCentralWidget( this->view_ );

    auto status = QMainWindow::statusBar();

    status->showMessage( QObject::tr( "Ready" ) );

    QMainWindow::setMinimumSize( QSize( 400, 500 ) );

    QObject::connect
    (
        this->address_, &QLineEdit::returnPressed,
        [ = ] () { this->ToURL( this->address_->text() ); }
    );

    auto list = new QListWidget;

    this->AddAssistWidget( "Console", list );

    QObject::connect
        (
            this->view_->Page(), &WebEnginePage::JavaScriptConsoleMessage,
            [ = ]
                (
                    QWebEnginePage::JavaScriptConsoleMessageLevel level,
                    const QString& message,
                    int line_number,
                    const QString& source_id
                )
            {
                list->addItem( message );
            }
        );

    QObject::connect
        (
            this->view_, &WebEngineView::loadStarted,
            [ = ] { list->clear(); }
        );
}

void MainWindow::AddAssistWidget( const QString& title, QWidget* widget )
{
    auto dock = new QDockWidget( title );

    dock->setWidget( widget );

    QMainWindow::addDockWidget( Qt::RightDockWidgetArea, dock );

    this->toolbar_->addAction( dock->toggleViewAction() );

    //widget->setWindowFlags( Qt::Window );
    //widget->show();
}

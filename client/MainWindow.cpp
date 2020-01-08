//
// Created by 岳子剑 on 2019/9/27.
//


#include "MainWindow.hpp"

#include <QWebChannel>
#include <QWebEngineView>

//#include "WebEnginePage.hpp"
#include "WebEngineView.hpp"


MainWindow::MainWindow()
{
    this->SetupUI();
}

MainWindow::~MainWindow()
{
    //delete this->page_;

    //this->page_ = Q_NULLPTR;
}

void MainWindow::InstallPlugin()
{
    #ifdef _WIN32

    QLibrary library( "../../activex/Debug/activex.dll" );
    //QLibrary library( "../../activex/Release/activex.dll" );

    if ( library.load() )
    {
        typedef QWidget* ( *Function )( QWebEnginePage*, const QString& );

        auto CreateWidget = ( Function )( library.resolve( "CreateWidget" ) );

        if ( CreateWidget )
        {
            QWidget* widget = CreateWidget( this->view_->page(), "ax" );

            if ( widget )
            {
                this->AddPluginWidget( widget );
            }
        }
    }
    else
    {
        QMessageBox::warning( this, tr( "Error" ), library.errorString() );
    }

    #else

    auto label = new QLabel;

    label->setAlignment( Qt::AlignCenter );
    label->setMargin( 20 );
    label->setText( "Windows ActiveX Control" );

    this->AddPluginWidget( label );

    #endif
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

    this->nav_address_->setText( this->view_->url().toDisplayString() );
}

void MainWindow::SetupUI()
{
    auto toolbar = new QToolBar();

    toolbar->setFloatable( false );
    toolbar->setMovable( false );

    auto nav_back    = new QAction( tr( "Back"    ) );
    auto nav_forward = new QAction( tr( "Forward" ) );
    auto nav_refresh = new QAction( tr( "Refresh" ) );

    this->nav_address_ = new QLineEdit;

    toolbar->addAction( nav_back );
    toolbar->addAction( nav_forward );
    toolbar->addAction( nav_refresh );

    toolbar->addWidget( this->nav_address_ );

    QMainWindow::addToolBar( Qt::TopToolBarArea, toolbar );

    auto status = QMainWindow::statusBar();

    status->showMessage( tr( "Ready" ) );

    QMainWindow::setMinimumSize( QSize( 800, 500 ) );

    this->view_ = new WebEngineView;

    QObject::connect
    (
        this->nav_address_, &QLineEdit::returnPressed,
        [ = ] () { this->ToURL( this->nav_address_->text() ); }
    );

    QMainWindow::setCentralWidget( this->view_ );
}

void MainWindow::AddPluginWidget( QWidget* widget )
{
    //auto dock = new QDockWidget;

    //dock->setWidget( widget );

    //QMainWindow::addDockWidget( Qt::RightDockWidgetArea, dock );

    widget->setWindowFlags( Qt::Window );
    widget->show();
}

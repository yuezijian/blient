//
// Created by ÔÀ×Ó½£ on 2019/9/27.
//


#include "MainWindow.hpp"

#include <QWebEngineView>

#ifdef _WIN32
#include <ActiveQt/QAxWidget>
#endif


MainWindow::MainWindow()
{
    auto toolbar = new QToolBar();

    toolbar->setFloatable( false );
    toolbar->setMovable( false );

    auto nav_back = new QAction( tr( "Back" ) );
    auto nav_forward = new QAction( tr( "Forward" ) );
    auto nav_refresh = new QAction( tr( "Refresh" ) );

    this->nav_address_ = new QLineEdit;

    toolbar->addAction( nav_back );
    toolbar->addAction( nav_forward );
    toolbar->addAction( nav_refresh );

    toolbar->addWidget( this->nav_address_ );

    QMainWindow::addToolBar( Qt::TopToolBarArea, toolbar );

    auto splitter = new QSplitter;

    QMainWindow::setCentralWidget( splitter );

    this->view_ = new QWebEngineView;

    splitter->addWidget( this->view_ );

    QObject::connect
    (
        this->nav_address_, &QLineEdit::returnPressed,
        [ = ] () { this->ToURL( this->nav_address_->text() ); }
    );

#ifdef _WIN32

    //if ( QLibrary::isLibrary( "editor.dll" ) )
    //{
    //    int i = 0;
    //}

    auto ax_widget = new QAxWidget;

    ax_widget->setControl( "{6F54E999-11EF-45DC-9E58-2858314C7016}" );

    QFile file( "D:/Project/blient/test.xml" );

    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QTextStream stream( &file );

        auto content = stream.readAll();

        auto result = ax_widget->dynamicCall( "ExecuteCommand( const QString&, bool, const QString& )", "FileOpenString", false, content );

        qDebug() << result;
    }

    splitter->addWidget( ax_widget );

#endif

    auto status = QMainWindow::statusBar();

    status->showMessage( tr( "Ready" ) );

    QMainWindow::setMinimumSize( QSize( 800, 500 ) );
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

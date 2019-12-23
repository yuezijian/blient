//
// Created by ���ӽ� on 2019/9/27.
//


#include "MainWindow.hpp"

#include <QWebEngineView>


MainWindow::MainWindow()
{
    auto toolbar = new QToolBar();

    toolbar->setFloatable( false );
    toolbar->setMovable( false );

    auto nav_back    = new QAction( tr( "Back"    ) );
    auto nav_forward = new QAction( tr( "Forward" ) );
    auto nav_refresh = new QAction( tr( "Refresh" ) );

    this->nav_address_ = new QLineEdit;

    toolbar->addAction( nav_back    );
    toolbar->addAction( nav_forward );
    toolbar->addAction( nav_refresh );

    toolbar->addWidget( this->nav_address_ );

    QMainWindow::addToolBar( Qt::TopToolBarArea, toolbar );

    this->view_ = new QWebEngineView;

    this->setCentralWidget( this->view_ );

    QObject::connect
        (
            this->nav_address_, &QLineEdit::returnPressed,
            [ = ]() { this->ToURL( this->nav_address_->text() ); }
        );

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

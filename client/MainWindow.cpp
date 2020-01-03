//
// Created by 岳子剑 on 2019/9/27.
//


#include "MainWindow.hpp"

#include <QWebChannel>
#include <QWebEngineView>

#include "WebEnginePage.hpp"


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

    //this->page_ = new WebEnginePage;

    //this->view_->setPage( this->page_ );

    splitter->addWidget( this->view_ );

    QObject::connect
        (
            this->nav_address_, &QLineEdit::returnPressed,
            [ = ] () { this->ToURL( this->nav_address_->text() ); }
        );

    QWidget* ax_widget = Q_NULLPTR;

    #ifdef _WIN32

    //QFile file( "D:/Project/blient/test.xml" );

    //if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    //{
    //    QTextStream stream( &file );

    //    auto content = stream.readAll();
    //}

    ax_widget = this->InstallActiveX();

    #else

    auto label = new QLabel;

    label->setAlignment( Qt::AlignCenter );
    label->setMargin( 20 );
    label->setText( "Will install ActiveX control in windows" );

    ax_widget = label;

    #endif

    if ( ax_widget )
    {
        splitter->addWidget( ax_widget );
    }

    auto status = QMainWindow::statusBar();

    status->showMessage( tr( "Ready" ) );

    QMainWindow::setMinimumSize( QSize( 800, 500 ) );
}

MainWindow::~MainWindow()
{
    //delete this->page_;

    //this->page_ = Q_NULLPTR;
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

#ifdef _WIN32
QWidget* MainWindow::InstallActiveX()
{
    //QLibrary library( "../activex/activex.dll" );
    QLibrary library( "../../activex/Debug/activex.dll" );

    if ( library.load() )
    {
        typedef QWidget* ( *Function )( QWebEnginePage*, const QString& name );

        auto CreateWidgetAX = ( Function )( library.resolve( "CreateWidgetAX" ) );

        if ( CreateWidgetAX )
        {
            return CreateWidgetAX( this->view_->page(), "ax" );
        }
    }
    else
    {
        QMessageBox::warning( this, tr( "Error" ), library.errorString() );
    }

    return Q_NULLPTR;
}
#endif

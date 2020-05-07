//
// Created by 岳子剑 on 2020/02/14.
//


#include "ConsoleWidget.hpp"

#include "engine/WebEnginePage.hpp"


ConsoleWidget::ConsoleWidget( WebEnginePage* page )
{
    //auto toolbar = new QToolBar;
    //
    //toolbar->setMovable( false );
    //
    //QMainWindow::addToolBar( toolbar );
    //
    //auto ac = new QAction( QObject::tr( "ac" ) );
    //
    //toolbar->addAction( ac );

    auto model = new QStandardItemModel;

    auto list = new QListView;

    list->setModel( model );
    list->setWordWrap( true );

    //list->setItemDelegate();

    QMainWindow::setCentralWidget( list );

    auto function = [ model ]
        (
            QWebEnginePage::JavaScriptConsoleMessageLevel level,
            const QString& message,
            int line_number,
            const QString& source_id
        )
    {
        auto item = new QStandardItem;

        switch ( level )
        {
            case QWebEnginePage::WarningMessageLevel:
            {
                item->setBackground( QColor( "#FFFBE5" ) );
                item->setForeground( QColor( "#5D3C00" ) );

                break;
            }
            case QWebEnginePage::ErrorMessageLevel:
            {
                item->setBackground( QColor( "#FFF0F0" ) );
                item->setForeground( QColor( "#FF0000" ) );

                break;
            }
            default:
                ;
        }

        auto text = message;

        if ( !source_id.isEmpty() )
        {
            text += QString( "\n%1:%2" ).arg( source_id ).arg( line_number );;
        }

        item->setText( text );

        model->appendRow( item );
    };

    QObject::connect( page, &WebEnginePage::JavaScriptConsoleMessage, function );
}

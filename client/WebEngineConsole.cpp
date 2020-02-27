//
// Created by 岳子剑 on 2019/02/14.
//


#include "WebEngineConsole.hpp"


WebEngineConsole::WebEngineConsole()
{
    auto layout = new QHBoxLayout;

    auto splitter = new QSplitter( Qt::Vertical );

    auto list = new QListWidget;

    auto button = new QPushButton( "Test" );

    layout->addWidget( splitter );

    layout->setMargin( 0 );

    splitter->addWidget( button );
    splitter->addWidget( list );

    QWidget::setLayout( layout );
}

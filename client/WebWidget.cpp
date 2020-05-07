//
// Created by 岳子剑 on 2020/05/06.
//


#include "WebWidget.hpp"

#include <QSplitter>
#include <QVBoxLayout>

#include "engine/WebEnginePage.hpp"
#include "engine/WebEngineView.hpp"

#include "engine/auxiliary/ConsoleWidget.hpp"


WebWidget::WebWidget()
{
    auto view = new WebEngineView( this );
    auto page = new WebEnginePage( view );

    view->setPage( page );
    view->show();

    auto splitter = new QSplitter( Qt::Horizontal );

    splitter->addWidget( view );
    splitter->addWidget( new ConsoleWidget( page ) );
    splitter->setCollapsible( 0, false );

    auto layout = new QVBoxLayout;

    layout->addWidget( splitter );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );

    QWidget::setLayout( layout );

    this->view_ = view;
}

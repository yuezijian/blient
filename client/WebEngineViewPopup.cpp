//
// Created by 岳子剑 on 2019/03/18.
//


#include "WebEngineViewPopup.hpp"

#include <QVBoxLayout>

#include "WebEngineView.hpp"


WebEngineViewPopup::WebEngineViewPopup()
{
    this->view_ = new WebEngineView;

    this->view_->setFocus();

    auto layout = new QVBoxLayout;

    layout->addWidget( this->view_ );
    layout->setContentsMargins( 0, 0, 0, 0 );

    QWidget::setLayout( layout );

    QObject::connect( this->view_->page(), &QWebEnginePage::windowCloseRequested, this, &QWidget::close );
}

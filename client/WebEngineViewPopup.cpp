//
// Created by 岳子剑 on 2019/03/18.
//


#include "WebEngineViewPopup.hpp"

#include <QVBoxLayout>
#include <QWindow>

#include "WebEngineView.hpp"


WebEngineViewPopup::WebEngineViewPopup()
{
    QWidget::setAttribute( Qt::WA_DeleteOnClose );
    QWidget::setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

    this->view_ = new WebEngineView;

    this->view_->setFocus();

    auto layout = new QVBoxLayout;

    layout->addWidget( this->view_ );
    layout->setContentsMargins( 0, 0, 0, 0 );

    QWidget::setLayout( layout );

    QObject::connect
        (
            this->view_->page(), &QWebEnginePage::geometryChangeRequested, [ this ]( const QRect& new_geometry )
            {
                if ( auto window = QWidget::windowHandle() )
                {
                    QWidget::setGeometry( new_geometry.marginsRemoved( window->frameMargins() ) );
                }

                QWidget::show();

                this->view_->setFocus();
            }
        );

    QObject::connect( this->view_->page(), &QWebEnginePage::windowCloseRequested, this, &QWidget::close );
}

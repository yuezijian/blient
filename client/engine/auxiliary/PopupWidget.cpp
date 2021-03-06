//
// Created by 岳子剑 on 2019/03/18.
//


#include "PopupWidget.hpp"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QWindow>

#include "engine/WebEngineView.hpp"


PopupWidget::PopupWidget()
{
    QWidget::setAttribute( Qt::WA_DeleteOnClose );
    QWidget::setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

    this->edit_ = new QLineEdit( this );

    this->edit_->setReadOnly( true );

    this->view_ = new WebEngineView;

    this->view_->setFocus();

    auto layout = new QVBoxLayout;

    layout->addWidget( this->edit_ );
    layout->addWidget( this->view_ );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    QWidget::setLayout( layout );

    QObject::connect
        (
            this->view_, &WebEngineView::urlChanged, [this]( const QUrl& url )
            {
                this->edit_->setText( url.toDisplayString() );
            }
        );

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

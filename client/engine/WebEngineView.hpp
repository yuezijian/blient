//
// Created by 岳子剑 on 2019/09/25.
//


#ifndef BLIENT__CLIENT__WEB_ENGINE_VIEW__HPP
#define BLIENT__CLIENT__WEB_ENGINE_VIEW__HPP


#include <QWebEngineView>


class WebEnginePage;


class WebEngineView : public QWebEngineView
{
Q_OBJECT

public:
    explicit WebEngineView( QWidget* parent = Q_NULLPTR );

    [[nodiscard]] int LoadProgress() const { return this->load_progress_; }

protected:
    //bool event( QEvent* event ) override;

    //bool eventFilter( QObject* object, QEvent* event ) override;

    QWebEngineView* createWindow( QWebEnginePage::WebWindowType type ) override;

private:
    int load_progress_ = 0;
};


#endif

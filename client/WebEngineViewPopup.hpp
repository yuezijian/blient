//
// Created by 岳子剑 on 2019/03/18.
//


#ifndef BLIENT__CLIENT__WEB_ENGINE_VIEW_POPUP__HPP
#define BLIENT__CLIENT__WEB_ENGINE_VIEW_POPUP__HPP


#include <QWebEngineView>


class WebEngineView;


class WebEngineViewPopup : public QWidget
{
Q_OBJECT

public:
    WebEngineViewPopup();

    [[nodiscard]] WebEngineView* View() const { return this->view_; }

private:
    WebEngineView* view_ = Q_NULLPTR;
};


#endif

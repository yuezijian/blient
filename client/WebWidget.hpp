//
// Created by 岳子剑 on 2020/05/06.
//


#ifndef BLIENT__CLIENT__WEB_WIDGET__HPP
#define BLIENT__CLIENT__WEB_WIDGET__HPP


#include <QWidget>


class WebEngineView;


class WebWidget : public QWidget
{
Q_OBJECT

public:
    WebWidget();

    [[nodiscard]] WebEngineView* View() const { return this->view_; }

private:
    WebEngineView* view_ = Q_NULLPTR;
};


#endif

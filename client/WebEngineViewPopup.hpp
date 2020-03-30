//
// Created by 岳子剑 on 2019/03/18.
//


#ifndef BLIENT__CLIENT__WEB_ENGINE_VIEW_POPUP__HPP
#define BLIENT__CLIENT__WEB_ENGINE_VIEW_POPUP__HPP


#include <QWebEngineView>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QProgressBar;
class QWebEngineProfile;
QT_END_NAMESPACE


class WebEngineView;


class WebEngineViewPopup : public QWidget
{
Q_OBJECT

public:
    WebEngineViewPopup();

    [[nodiscard]] WebEngineView* View() const { return this->view_; }

private:
    QLineEdit* edit_ = Q_NULLPTR;

    WebEngineView* view_ = Q_NULLPTR;
};


#endif

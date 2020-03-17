//
// Created by 岳子剑 on 2019/09/27.
//


#ifndef BLIENT__CLIENT__MAIN_WINDOW__HPP
#define BLIENT__CLIENT__MAIN_WINDOW__HPP


#include <QMainWindow>


QT_BEGIN_NAMESPACE
class QLineEdit;
class QWebEngineProfile;
QT_END_NAMESPACE


class Client;
class TabWidget;
class WebEngineView;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow( Client* client, QWebEngineProfile* profile );

    //void InstallPlugin();

    Client* ClientInstance() { return this->client_; }

    [[nodiscard]] TabWidget* Tab() const { return this->tab_; }

private:
    void SetupUI();

    void AddAssistWidget( const QString& title, QWidget* widget, int width = 0 );

private:
    Client* client_ = Q_NULLPTR;

    QToolBar* tool_ = Q_NULLPTR;

    QLineEdit* edit_ = Q_NULLPTR;

    TabWidget* tab_ = Q_NULLPTR;
};


#endif

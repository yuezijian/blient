//
// Created by 岳子剑 on 2019/09/27.
//


#ifndef BLIENT__CLIENT__MAIN_WINDOW__HPP
#define BLIENT__CLIENT__MAIN_WINDOW__HPP


#include <QtWidgets>


class WebEngineView;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

    void InstallPlugin();

    void ToURL( const QString& address );

private:
    void SetupUI();

    void AddAssistWidget( const QString& title, QWidget* widget, int width = 0 );

private:
    QToolBar* toolbar_ = Q_NULLPTR;

    QLineEdit* address_ = Q_NULLPTR;

    WebEngineView* view_ = Q_NULLPTR;
};


#endif

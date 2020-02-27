//
// Created by 岳子剑 on 2019/09/27.
//


#ifndef MAIN_WINDOW__HPP
#define MAIN_WINDOW__HPP


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

    void AddPluginWidget( QWidget* widget );

private:
    QLineEdit* address_ = Q_NULLPTR;

    WebEngineView* view_ = Q_NULLPTR;
};


#endif

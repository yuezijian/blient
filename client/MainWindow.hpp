//
// Created by 岳子剑 on 2019/9/27.
//


#ifndef MAIN_WINDOW__HPP
#define MAIN_WINDOW__HPP


#include <QtWidgets>


class QWebEngineView;

//class WebEnginePage;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void ToURL( const QString& address );

#ifdef _WIN32
private:
    void InstallActiveX();
#endif

private:
    QLineEdit* nav_address_ = Q_NULLPTR;

    QWebEngineView* view_ = Q_NULLPTR;

    //WebEnginePage* page_ = Q_NULLPTR;
};


#endif

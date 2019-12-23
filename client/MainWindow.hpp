//
// Created by ÔÀ×Ó½£ on 2019/9/27.
//


#ifndef MAIN_WINDOW__HPP
#define MAIN_WINDOW__HPP


#include <QtWidgets>


class QWebEngineView;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

    void ToURL( const QString& address );

private:
    QLineEdit* nav_address_ = Q_NULLPTR;

    QWebEngineView* view_ = Q_NULLPTR;
};


#endif

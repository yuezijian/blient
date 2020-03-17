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


class TabWidget;
class WebEngineView;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow( QWebEngineProfile* profile );

    //void InstallPlugin();

    void ToURL( const QString& address );

private:
    void SetupUI();

    void AddAssistWidget( const QString& title, QWidget* widget, int width = 0 );

private:
    QToolBar* toolbar_ = Q_NULLPTR;

    QLineEdit* address_ = Q_NULLPTR;

    TabWidget* tab_ = Q_NULLPTR;
};


#endif

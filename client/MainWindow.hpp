//
// Created by 岳子剑 on 2019/9/27.
//


#ifndef MAIN_WINDOW__HPP
#define MAIN_WINDOW__HPP


#include <QtWidgets>


//class WebEnginePage;
class QWebEngineView;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void InstallPlugin();

    void ToURL( const QString& address );

private:
    void SetupUI();

    void AddPluginWidget( QWidget* widget );

private:
    QLineEdit* nav_address_ = Q_NULLPTR;

    QSplitter* splitter_ = Q_NULLPTR;

    QWebEngineView* view_ = Q_NULLPTR;

    //WebEnginePage* page_ = Q_NULLPTR;
};


#endif

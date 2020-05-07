//
// Created by 岳子剑 on 2020/02/14.
//


#ifndef BLIENT__CLIENT__ENGINE__AUXILIARY__CONSOLE_WIDGET__HPP
#define BLIENT__CLIENT__ENGINE__AUXILIARY__CONSOLE_WIDGET__HPP


#include <QtWidgets>


class WebEnginePage;


class ConsoleWidget : public QMainWindow
{
public:
    explicit ConsoleWidget( WebEnginePage* page );
};


#endif

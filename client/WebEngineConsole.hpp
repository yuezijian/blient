//
// Created by 岳子剑 on 2020/02/14.
//


#ifndef BLIENT__CLIENT__WEB_ENGINE_CONSOLE__HPP
#define BLIENT__CLIENT__WEB_ENGINE_CONSOLE__HPP


#include <QtWidgets>


class WebEnginePage;


class WebEngineConsole : public QMainWindow
{
public:
    explicit WebEngineConsole( WebEnginePage* page );
};


#endif

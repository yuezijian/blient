//
// Created by 岳子剑 on 2020/01/09.
//


#ifndef BLIENT__CLIENT__CLIENT__HPP
#define BLIENT__CLIENT__CLIENT__HPP


#include "_client.hpp"

#include "../base/Program.hpp"

#include <QVector>

// BLIENT_CLIENT__EXPORT


class MainWindow;


class Client : public Program
{
public:
    int Main( int argc, char* argv[] ) override;

    [[nodiscard]] Version InstanceVersion() const override;

    MainWindow* CreateWindow();

private:
    QVector< MainWindow* > windows_;
};


#endif

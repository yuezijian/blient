#include "Client.hpp"

#include <QtWidgets>

#include "MainWindow.hpp"


int Client::Main( int argc, char* argv[] )
{
    // QApplication 对象创建之前
    //
    // 调用

    QApplication::setOrganizationName( "Luna" );

    // QApplication 对象创建之前
    //
    // 结束

    QApplication application( argc, argv );

    MainWindow window;

    //window.InstallPlugin();

    window.showMaximized();

    return QApplication::exec();
}

Version Client::InstanceVersion() const
{
    return Version( 0, 0, 1 );
}

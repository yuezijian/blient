#include <QtWidgets>

#include "MainWindow.hpp"

#ifdef _WIN32
    #include <ActiveQt/QAxWidget>
#endif


int main( int argc, char* argv[] )
{
    // QApplication 对象创建之前
    //
    // 调用

    QApplication::setOrganizationName( "Luna" );

    // QApplication 对象创建之前
    //
    // 结束

    QApplication application( argc, argv );

    #ifdef _WIN32

    //if ( QLibrary::isLibrary( "editor.dll" ) )
    //{
    //    int i = 0;
    //}

    QAxWidget widget;

    widget.setControl( "{6F54E999-11EF-45DC-9E58-2858314C7016}" );
    widget.show();

    #else

    MainWindow window;

    window.ToURL( "http://10.68.4.11/webcomm" );
    window.showMaximized();

    #endif

    return QApplication::exec();
}

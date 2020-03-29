//
// Created by 岳子剑 on 2020/03/29.
//

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <QApplication>
#include <QDebug>
#include <QListWidget>


#ifdef WIN32
int APIENTRY wWinMain
(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow
)
{
    int   argc   = 1;
    char* argv[] = { "test_executable.exe" };
#else
int main( int argc, char* argv[] )
{
#endif
    QApplication application( argc, argv );

    QListWidget widget;

    auto arguments = QCoreApplication::arguments();

    widget.addItem( "我就是那个exe，名字叫做：" );

    for ( auto& arg : arguments )
    {
        widget.addItem( arg );
    }

    widget.show();

    return QApplication::exec();
}

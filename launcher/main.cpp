//
// Created by 岳子剑 on 2020/01/09.
//


#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <QApplication>
#include <QDebug>
#include <QMessageBox>

#include "../base/Program.hpp"
#include "../base/Util.hpp"


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
    char* argv[] = { "launcher.exe" };
#else
int main( int argc, char* argv[] )
{
#endif
    auto library = Util::Library( "client" );

    if ( library.load() )
    {
        typedef Program* ( *Function )();

        auto CreateProgram = ( Function )( library.resolve( "CreateProgram" ) );

        if ( CreateProgram )
        {
            auto program = CreateProgram();

            if ( program )
            {
                //auto version = program->InstanceVersion();

                // 在这里检查更新

                auto code = program->Main( argc, argv );

                delete program;

                return code;
            }
        }
    }

    {
        QApplication application( argc, argv );

        QMessageBox::critical
        (
            Q_NULLPTR,
            QObject::tr( "无法加载模块" ),
            library.errorString()
        );
    }

    return 0;
}

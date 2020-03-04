#ifdef WIN32
#include <atlbase.h>
#endif

#include <QApplication>
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
    char* argv[] = { "" };

    //ATLASSERT( SUCCEEDED( CoInitialize( NULL ) ) );

    //CComModule module;

    //module.Init( 0, hInstance );
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
            QObject::tr( "Error" ),
            library.errorString()
        );
    }

    return 0;
}

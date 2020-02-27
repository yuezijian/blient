#include <QApplication>
#include <QMessageBox>

#include "../base/Program.hpp"
#include "../base/Util.hpp"


int main( int argc, char* argv[] )
{
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

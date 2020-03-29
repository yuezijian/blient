//
// Created by 岳子剑 on 2020/01/09.
//


#include "Client.hpp"

#include <ClientConfig.hpp>

#include <QApplication>
#include <QFile>

#include <QWebEngineProfile>
#include <QWebEngineUrlScheme>

#include "MainWindow.hpp"
#include "TabWidget.hpp"
#include "WebEngineUrlSchemeHandlerExecutable.hpp"


int Client::Main( int argc, char* argv[] )
{
    // QApplication 对象创建之前
    //
    // 调用

    QCoreApplication::setOrganizationName( "Luna" );

    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
    QCoreApplication::setAttribute( Qt::AA_UseHighDpiPixmaps    );

    QWebEngineUrlScheme::registerScheme( QWebEngineUrlScheme( "executable" ) );

    // QApplication 对象创建之前
    //
    // 结束

    QApplication application( argc, argv );

    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler( "executable", new WebEngineUrlSchemeHandlerExecutable );

    //QFile file( ":/blient.js" );
    //
    //if ( file.open( QFile::ReadOnly ) )
    //{
    //    //QWebEngineScript script;
    //    //
    //    //script.setInjectionPoint( QWebEngineScript::DocumentCreation );
    //    //script.setRunsOnSubFrames( true );
    //    //script.setWorldId( QWebEngineScript::MainWorld );
    //    //script.setSourceCode( file.readAll() );
    //    //
    //    //QWebEngineProfile::defaultProfile()->scripts()->insert( script );
    //}

    {
        auto window = this->CreateWindow();

        //window->Tab()->SetURL( "localhost:3000" );
    }

    auto code = QApplication::exec();

    {
        for ( auto window : this->windows_ )
        {
            delete window;
        }
    }

    return code;
}

Version Client::InstanceVersion() const
{
    return Version
        (
            CLIENT_VERSION_MAJOR,
            CLIENT_VERSION_MINOR,
            CLIENT_VERSION_PATCH
        );
}

MainWindow* Client::CreateWindow()
{
    auto profile = QWebEngineProfile::defaultProfile();

    auto window = new MainWindow( this, profile );

    window->showMaximized();

    this->windows_.append( window );

    QObject::connect( window, &QObject::destroyed, [ this, window ]() { this->windows_.removeOne( window ); } );

    return window;
}

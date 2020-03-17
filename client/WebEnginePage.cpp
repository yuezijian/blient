//
// Created by 岳子剑 on 2019/11/1.
//


#include "WebEnginePage.hpp"

#include <QWebChannel>
#include <QWebEngineSettings>


WebEnginePage::WebEnginePage()
{
    QWebEnginePage::setWebChannel( new QWebChannel );
}

void WebEnginePage::javaScriptConsoleMessage( QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString& message, int line_number, const QString& source_id )
{
    emit JavaScriptConsoleMessage( level, message, line_number, source_id );
}

//QWebEnginePage* WebEnginePage::createWindow( QWebEnginePage::WebWindowType type )
//{
//    auto page = QWebEnginePage::createWindow( type );
//
//    //switch ( type )
//    //{
//    //    case QWebEnginePage::WebBrowserWindow:
//    //        break;
//    //    case QWebEnginePage::WebBrowserTab:
//    //        break;
//    //    case QWebEnginePage::WebDialog:
//    //        break;
//    //    default:
//    //        ;
//    //}
//
//    //return QWebEngineView::createWindow( type );
//
//    qDebug() << type;
//
//    qDebug() << page;
//    qDebug() << this;
//
//    return page;
//}

//
// Created by 岳子剑 on 2019/11/1.
//

#ifndef WEB_ENGINE_PAGE__HPP
#define WEB_ENGINE_PAGE__HPP


#include <QWebEnginePage>


class WebEngineChannelObject;


class WebEnginePage : public QWebEnginePage
{
Q_OBJECT

Q_SIGNALS:
    void JavaScriptConsoleMessage
        (
            QWebEnginePage::JavaScriptConsoleMessageLevel level,
            const QString& message,
            int line_number,
            const QString& source_id
        );

protected:
    void javaScriptConsoleMessage
        (
            QWebEnginePage::JavaScriptConsoleMessageLevel level,
            const QString& message,
            int line_number,
            const QString& source_id
        ) override;
};


#endif

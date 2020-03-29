//
// Created by 岳子剑 on 2019/11/01.
//


#ifndef BLIENT__CLIENT__WEB_ENGINE_PAGE__HPP
#define BLIENT__CLIENT__WEB_ENGINE_PAGE__HPP


#include <QWebEnginePage>


class WebEngineChannelObject;


class WebEnginePage : public QWebEnginePage
{
Q_OBJECT

public:
    explicit WebEnginePage( QObject* parent = Q_NULLPTR );

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

//
// Created by 岳子剑 on 2020/03/29.
//

#ifndef BLIENT__WEB_ENGINE_URL_SCHEME_HANDLER__HPP
#define BLIENT__WEB_ENGINE_URL_SCHEME_HANDLER__HPP


#include <QWebEngineUrlSchemeHandler>


QT_BEGIN_NAMESPACE

class QWebEngineUrlRequestJob;

QT_END_NAMESPACE


class WebEngineUrlSchemeHandlerExecutable : public QWebEngineUrlSchemeHandler
{
Q_OBJECT

public:
    void requestStarted( QWebEngineUrlRequestJob* request ) override;
};


#endif

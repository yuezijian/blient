//
// Created by 岳子剑 on 2019/02/12.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__AX_WIDGET__HPP
#define BLIENT__PLUGIN__ACTIVEX__AX_WIDGET__HPP


#include <QtWidgets/QtWidgets>

#include <QWebEnginePage>
#include <QWebChannel>

#include "WebEngineChannelObject.hpp"


class AxWidget : public QWidget
{
public:
    AxWidget()
    {
        this->object_ = new WebEngineChannelObject;

        QObject::connect
            (
                this->object_, &WebEngineChannelObject::AXC_Editor_FileOpenString,
                [ = ] ( const QString& content )
                {
                    qDebug() << content;
                }
            );
    }

    WebEngineChannelObject* ChannelObject()
    {
        return this->object_;
    }

private:
    WebEngineChannelObject* object_ = Q_NULLPTR;
};


#endif

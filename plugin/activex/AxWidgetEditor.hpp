//
// Created by 岳子剑 on 2019/02/12.
//


#ifndef BLIENT__PLUGIN__ACTIVEX__EDITOR__HPP
#define BLIENT__PLUGIN__ACTIVEX__EDITOR__HPP


#include <QtWidgets/QtWidgets>


#include <QWebEnginePage>
#include <QWebChannel>

#include "WebEngineChannelObject.hpp"


#include <ActiveQt/QAxWidget>


class AxWidgetEditor : public QAxWidget
{
public:
    AxWidgetEditor() : QAxWidget( "{6F54E999-11EF-45DC-9E58-2858314C7016}" )
    {
    }

protected:
    //bool translateKeyEvent( int message, int keycode ) const override
    //{
    //    return QAxWidget::translateKeyEvent( message, keycode );
    //}
};


#endif

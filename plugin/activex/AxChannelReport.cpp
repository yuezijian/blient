//
// Created by 岳子剑 on 2020/03/03.
//


#include "AxChannelReport.hpp"

#include <QDebug>

#include "AxWidgetReport.hpp"


AxChannelReport::AxChannelReport( AxWidgetReport* report ) : report_( report )
{
}

QVariant AxChannelReport::FileOpenString( const QVariant& value )
{
    qDebug() << "Report Called";

    return QVariant();
}

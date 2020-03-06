//
// Created by 岳子剑 on 2019/03/03.
//


#include "AxWidgetReport.hpp"

#include <QAxObject>


AxWidgetReport::AxWidgetReport() :
    QAxWidget( "{44CBB5DE-5AFB-4c3d-8F3F-0F70CA5372AD}" )
{
    this->report_ = new QAxObject( "{F9364159-6AED-4f9c-8BAF-D7C7ED6160A8}" );

    //this->report_->dynamicCall( "LoadFromFile(string)", "d:/h.grf" );

    //QAxWidget::dynamicCall( "Report", this->report_->asVariant() );
    //QAxWidget::dynamicCall( "Start()" );
}

bool AxWidgetReport::translateKeyEvent( int message, int keycode ) const
{
    return QAxWidget::translateKeyEvent( message, keycode );
}

QVariant AxWidgetReport::FileOpenString( const QVariant& value )
{
    return QVariant();
}

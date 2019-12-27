//
// Created by 岳子剑 on 2019/11/5.
//

#ifndef WEB_ENGINE_CHANNEL_OBJECT__HPP
#define WEB_ENGINE_CHANNEL_OBJECT__HPP


#include <QObject>
#include <QVariant>


class WebEngineChannelObject : public QObject
{
Q_OBJECT

    // 调用前台页面的 JS 逻辑

    Q_PROPERTY( QString my_property MEMBER my_property_ NOTIFY OnPropertyChange )

Q_SIGNALS:
    void OnPropertyChange( const QString& );

    // 来自前台页面的 JS 调用

public Q_SLOTS:
    QVariant FileOpenString( const QVariant& value );

private:
    QString my_property_;
};


#endif

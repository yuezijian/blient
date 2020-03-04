//
// Created by 岳子剑 on 2019/11/05.
//


#ifndef WEB_ENGINE_CHANNEL_OBJECT__HPP
#define WEB_ENGINE_CHANNEL_OBJECT__HPP


#include <QObject>
#include <QVariant>


class AxWidgetEditor;


class WebEngineChannelObject : public QObject
{
Q_OBJECT

public:
    explicit WebEngineChannelObject( AxWidgetEditor* editor );

    // 调用前台页面的 JS 逻辑

    Q_PROPERTY( QString my_property MEMBER my_property_ NOTIFY OnPropertyChange )

Q_SIGNALS:
    void OnPropertyChange( const QString& );

public Q_SLOTS:

    // 来自前台业务的 JS 调用

    QVariant FileOpenString( const QVariant& value );

private:
    AxWidgetEditor* editor_ = Q_NULLPTR;

    QString my_property_;
};


#endif

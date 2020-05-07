//
// Created by 岳子剑 on 2020/03/11.
//


#ifndef BLIENT__CLIENT__TAB_WIDGET__HPP
#define BLIENT__CLIENT__TAB_WIDGET__HPP


#include <QTabWidget>
#include <QWebEnginePage>


class WebWidget;


class TabWidget : public QTabWidget
{
Q_OBJECT

public:
    TabWidget();

    [[nodiscard]] WebWidget* ActiveWidget() const;

    [[nodiscard]] WebWidget* Widget( int index ) const;

signals:
    void ChangeURL( const QUrl& url );

    void ChangeTitle( const QString& title );

    void LoadProgress( int progress );

public slots:
    WebWidget* CreateWidget();
    WebWidget* CreateWidgetActive();

    void CloseWidget( int index );

    void CloseWidgetActive();

    void SetURL( const QString& url );

    void TriggerWebAction( QWebEnginePage::WebAction action );

private slots:
    void ChangeCurrent( int index );
};


#endif

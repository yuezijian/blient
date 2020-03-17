//
// Created by 岳子剑 on 2020/03/11.
//


#ifndef BLIENT__CLIENT__TAB_WIDGET__HPP
#define BLIENT__CLIENT__TAB_WIDGET__HPP


#include <QTabWidget>


class WebEngineView;


class TabWidget : public QTabWidget
{
Q_OBJECT

public:
    TabWidget();

    [[nodiscard]] WebEngineView* ActiveView() const;

signals:
    void ChangeURL( const QUrl& url );

public slots:
    WebEngineView* CreateTab();

    void SetURL( const QUrl& url );
};


#endif

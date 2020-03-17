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

    [[nodiscard]] WebEngineView* View() const;

signals:
    void ChangeURL( const QUrl& url );

    void ChangeTitle( const QString& title );

public slots:
    void CloseTab( int index );

    WebEngineView* CreateView();
    WebEngineView* CreateViewBackground();

    void SetURL( const QUrl& url );
};


#endif

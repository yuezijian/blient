//
// Created by 岳子剑 on 2020/03/11.
//


#ifndef BLIENT__CLIENT__TAB_WIDGET__HPP
#define BLIENT__CLIENT__TAB_WIDGET__HPP


#include <QTabWidget>
#include <QWebEnginePage>


class WebEngineView;


class TabWidget : public QTabWidget
{
Q_OBJECT

public:
    TabWidget();

    [[nodiscard]] WebEngineView* ActiveView() const;

    [[nodiscard]] WebEngineView* View( int index ) const;

signals:
    void ChangeURL( const QUrl& url );

    void ChangeTitle( const QString& title );

    void LoadProgress( int progress );

public slots:
    WebEngineView* CreateView();
    WebEngineView* CreateViewBackground();

    void CloseActiveView();

    void CloseView( int index );

    void SetURL( const QString& url );

    void TriggerWebAction( QWebEnginePage::WebAction action );

private slots:
    void ChangeCurrent( int index );
};


#endif

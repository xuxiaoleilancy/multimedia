#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sdlwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget* wdg();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pshBtnClick_clicked();
private:
    Ui::MainWindow *ui;

	QList<QWidget*> m_listWdg;
	QList<QWidget*> m_listWdgTotal;
	int iRenderCount;
    SDLWidget* m_pSdlWdg;
};

#endif // MAINWINDOW_H

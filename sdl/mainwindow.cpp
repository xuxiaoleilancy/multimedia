#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //m_listWdg.append( ui->pshBtnClick );

	iRenderCount = 2;
	
	m_listWdgTotal.append(ui->widget_1_1);
	m_listWdgTotal.append(ui->widget_1_2);
	m_listWdgTotal.append(ui->widget_1_3);
	m_listWdgTotal.append(ui->widget_1_4);
	m_listWdgTotal.append(ui->widget_1_5);
	m_listWdgTotal.append(ui->widget_2_1);
	m_listWdgTotal.append(ui->widget_2_2);
	m_listWdgTotal.append(ui->widget_2_3);
	m_listWdgTotal.append(ui->widget_2_4);
	m_listWdgTotal.append(ui->widget_2_5);
	m_listWdgTotal.append(ui->widget_3_1);
	m_listWdgTotal.append(ui->widget_3_2);
	m_listWdgTotal.append(ui->widget_3_3);
	m_listWdgTotal.append(ui->widget_3_4);
	m_listWdgTotal.append(ui->widget_3_5);
	m_listWdgTotal.append(ui->widget_4_1);
	m_listWdgTotal.append(ui->widget_4_2);
	m_listWdgTotal.append(ui->widget_4_3);
	m_listWdgTotal.append(ui->widget_4_4);
	m_listWdgTotal.append(ui->widget_4_5);
	m_listWdgTotal.append(ui->widget_5_1);
	m_listWdgTotal.append(ui->widget_5_2);
	m_listWdgTotal.append(ui->widget_5_3);
	m_listWdgTotal.append(ui->widget_5_4);
	m_listWdgTotal.append(ui->widget_5_5);

	foreach(QWidget* pWdg, m_listWdgTotal){
		pWdg->setVisible(false);
	}

	for (int i = 0; i < iRenderCount;i++)
	{
		m_listWdg.append(m_listWdgTotal[i]);
	}
	
    foreach( QWidget* pWdg , m_listWdg ){
		pWdg->setVisible(true);
		pWdg->setUpdatesEnabled(false);
    }

    m_pSdlWdg = new SDLWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_pSdlWdg->deleteLater();
    m_pSdlWdg = NULL;
}

QWidget *MainWindow::wdg()
{
    foreach(QWidget* pWdg , m_listWdg ){
        m_pSdlWdg->addWidget((void*)pWdg->winId());
    }

    m_pSdlWdg->start();

    return NULL;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if( NULL != m_pSdlWdg ){
        foreach(QWidget* pWdg , m_listWdg ){
            m_pSdlWdg->resize((void*)pWdg->winId(),pWdg->geometry());
        }
    }
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_pshBtnClick_clicked()
{
    QMessageBox msg;
    msg.exec();
}

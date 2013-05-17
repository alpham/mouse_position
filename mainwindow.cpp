#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    mouseEvent = new QMouseEvent(QEvent::Move,QPoint(0,0),Qt::NoButton,Qt::NoButton,Qt::NoModifier);
    qApp->installEventFilter(this);
    connect(this,SIGNAL(mouseMoved(QPoint)),this,SLOT(updateStatusBar(QPoint)));
}

MainWindow::~MainWindow()
{
}


void MainWindow::updateStatusBar(QPoint pos)
{
    setStatusTip(QString(" X = %1 \t Y = %2 ").arg(pos.x()).arg(pos.y()));
    emit statusBarUpdated();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
  }
  return false;
}

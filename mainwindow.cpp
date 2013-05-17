#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <fstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    lastRow = 0;
    ui->setupUi(this);
    qApp->installEventFilter(this);
    loadActions();
    loadConnections();
    ui->tableWidget->setItemPrototype(new QTableWidgetItem);
    ui->tableWidget->setColumnCount(colCount);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("Time")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("X Coordinate")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("Y Coordinate")));
    fileName = "row" ;
    loadFile(fileName);

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->globalPos().x()).arg(mouseEvent->globalPos().y()));
    loadRow(lastRow,QString("time,%1,%2").arg(mouseEvent->globalPos().x()).arg(mouseEvent->globalPos().y()));
    qDebug()<< QString("Mouse move (%1,%2)").arg(mouseEvent->globalPos().x()).arg(mouseEvent->globalPos().y()) << endl;
    ui->tableWidget->setCurrentCell(lastRow,0);
  }
  return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadActions()
{
    createActions();
    ui->mainToolBar->addAction(newRow);
    ui->mainToolBar->addAction(deleteRow);
    ui->mainToolBar->addAction(save);
}

void MainWindow::loadConnections()
{
    connect(newRow,SIGNAL(triggered()),this,SLOT(createRow()));
    connect(deleteRow,SIGNAL(triggered()),this,SLOT(removeRow()));
    connect(save,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->action_About,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->action_Quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->action_Add_new,SIGNAL(triggered()),this,SLOT(createRow()));
}

void MainWindow::createActions(){
    newRow = new QAction("&New",this);
    deleteRow = new QAction("&Delete",this);
    save = new QAction("&Save",this);
}

bool MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Library"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QString str;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int row =0 ;
    while (!in.atEnd()) {
        str=in.readLine();
        loadRow(row,str);
        row++;
    }
    QApplication::restoreOverrideCursor();
    return true;
}

void MainWindow::loadRow(int row,const QString ch)
{
    QString str(ch);
    QStringList list= str.split(",");
    int col=0;
    ui->tableWidget->insertRow(row);
    while(col< colCount){
        QTableWidgetItem *cell=new QTableWidgetItem;
        cell->setText(list[col]);
        ui->tableWidget->setItem(row,col,cell);

        col++;
    }
    lastRow = ui->tableWidget->rowCount();
}


void MainWindow::createRow()
{
    ui->tableWidget->insertRow(lastRow);
    lastRow++;
}

void MainWindow::removeRow()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    lastRow--;
}

bool MainWindow::saveFile(){
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Library"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    for(int row = 0 ;row < lastRow;row++) {
        for(int col = 0 ; col < colCount ; col++){
            out << ui->tableWidget->item(row,col)->text() << "," ;

        }
        out << endl;
    }
    QApplication::restoreOverrideCursor();
    return true;
}

void MainWindow::about()
{
}

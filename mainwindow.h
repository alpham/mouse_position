#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QMouseEvent *mouseEvent;
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void mouseMoved(QPoint);
    void statusBarUpdated();

private slots:
    void updateStatusBar(QPoint);

};

#endif // MAINWINDOW_H

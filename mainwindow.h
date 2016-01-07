#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int randomInt(int low, int high);
    int randomAngle(int low, int high);
    void initSettings();
    
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsLineItem *line;
    QGraphicsTextItem *text;

    bool checkAngle;
    int XrandomNum;
    int YrandomNum;
    int angle;

private slots:
    void OKbutton_clicked();
};

#endif // MAINWINDOW_H

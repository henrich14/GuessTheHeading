#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setFixedSize(650,640);
    setFixedSize(750,680);
    setWindowTitle("Guess The Heading");

    qsrand(QDateTime::currentDateTime().toTime_t());
    ui->estLineEdit->setText("");
    ui->estLineEdit->setAlignment(Qt::AlignCenter);
    ui->estLineEdit->setFocus();
    ui->realLabel->setText("");
    ui->realLabel->setAlignment(Qt::AlignCenter);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(ui->OKbutton, SIGNAL(clicked()), this, SLOT(OKbutton_clicked()));
    connect(ui->estLineEdit, SIGNAL(returnPressed()), ui->OKbutton, SLOT(animateClick()));

    initSettings();
    checkAngle = false;
    OKbutton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::randomInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

int MainWindow::randomAngle(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

void MainWindow::initSettings()
{
    scene->clear();

    XrandomNum = randomInt(-220,220);
    YrandomNum = randomInt(-220,220);
    angle = randomAngle(0,360);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);

    for(int i=1; i<=5; i++)
    {
        int radius = 60*i;
        ellipse = scene->addEllipse(-radius, -radius, radius*2,radius*2, blackpen);
    }

    for(int k=0; k<36; k++)
    {
        line = scene->addLine(0, -300, 0, -310, blackpen);
        line->setRotation(k*10);
    }

    QFont font;
    font.setPixelSize(15);
    font.setBold(false);
    font.setFamily("Calibri");

    text = scene->addText("360°", font);
    text->setPos(0,-300);

    text = scene->addText("90°", font);
    text->setPos(300,0);

    text = scene->addText("180°", font);
    text->setPos(0,300);

    text = scene->addText("270°", font);
    text->setPos(-300,0);
}

void MainWindow::OKbutton_clicked()
{
    int realAngle = (270 + angle) - 360 * qFloor((270 + angle)/360);

    if(ui->estLineEdit->text().isEmpty() && checkAngle == false)
    {
        initSettings();

        int rectSize = 16;
        int SrectSize = 8;

        QPen blackpen(Qt::black);
        QBrush blackBrush(Qt::black);
        blackpen.setWidth(1);
        rectangle = scene->addRect(XrandomNum, YrandomNum, rectSize, rectSize, blackpen, blackBrush);
        rectangle->setTransformOriginPoint(XrandomNum + rectSize/2, YrandomNum + rectSize/2);
        rectangle->setRotation(angle);

        for(int k=0; k<5; k++)
        {
            rectangle = scene->addRect(XrandomNum+20+k*(SrectSize+5), YrandomNum + rectSize/4, SrectSize, SrectSize, blackpen, blackBrush);
            rectangle->setTransformOriginPoint(XrandomNum + rectSize/2, YrandomNum + rectSize/2);
            rectangle->setRotation(angle);
        }
    }

    else if(!ui->estLineEdit->text().isEmpty() && checkAngle==false)
    {
        qDebug() << realAngle;
        ui->realLabel->setText(QString::number(realAngle));
        checkAngle = true;

        line = scene->addLine(-300, 0, 300, 0);
        line = scene->addLine(0, -300, 0, 300);
        line = scene->addLine(0, -300, 0, 300);
        line->setRotation(realAngle);


    }
    else if(!ui->estLineEdit->text().isEmpty() && checkAngle==true)
    {
        qDebug() << realAngle;
        ui->realLabel->setText("");
        ui->estLineEdit->setText("");
        checkAngle = false;
        ui->estLineEdit->setFocus();
        initSettings();

        int rectSize = 16;
        int SrectSize = 8;

        QPen blackpen(Qt::black);
        QBrush blackBrush(Qt::black);
        blackpen.setWidth(1);
        rectangle = scene->addRect(XrandomNum, YrandomNum, rectSize, rectSize, blackpen, blackBrush);
        rectangle->setTransformOriginPoint(XrandomNum + rectSize/2, YrandomNum + rectSize/2);
        rectangle->setRotation(angle);

        for(int k=0; k<5; k++)
        {
            rectangle = scene->addRect(XrandomNum+20+k*(SrectSize+5), YrandomNum + rectSize/4, SrectSize, SrectSize, blackpen, blackBrush);
            rectangle->setTransformOriginPoint(XrandomNum + rectSize/2, YrandomNum + rectSize/2);
            rectangle->setRotation(angle);
        }
    }


}

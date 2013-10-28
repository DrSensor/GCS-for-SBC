#include "slam.h"
#include "ui_slam.h"

SLAM::SLAM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SLAM)
{
    ui->setupUi(this);

//    QGraphicsPixmapItem *player;
//    QGraphicsScene scene;

//    scene.setSceneRect(-300, -300, 600, 600);
//    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
//    scene.addPixmap(QPixmap(":/object/logo.png"));
//    scene.setBackgroundBrush(QPixmap(":/background/kampung halaman.jpg"));
//    ui->fieldView->setScene(&scene);
//    ui->fieldView->setBackgroundBrush(Qt::black);
//    ui->fieldView->update();
}

SLAM::~SLAM()
{
    delete ui;
}

#include "streaming.h"
#include "ui_streaming.h"

#include <QDebug>

Streaming::Streaming(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Streaming)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->volume->setOrientation(Qt::Horizontal);

    connect(ui->url_edit, SIGNAL(returnPressed()), this, SLOT(openUrl()));
}

Streaming::~Streaming()
{
    delete ui;
}

bool Streaming::openUrl()
{
    QString url = ui->url_edit->text();

    if (url.isEmpty())
        return false;

    _media = new VlcMedia(url, _instance);

    _player->open(_media);
    return true;
}

void Streaming::on_play_button_toggled(bool checked)
{
    static bool url_valid = false;
    if (checked) {
        if (url_valid) ui->play_button->setText("Stop");
        url_valid = openUrl();
        qDebug() << "url is " << (url_valid ? "valid" : "not valid") << endl;
    } else {
        ui->play_button->setText("Play");
        _player->stop();
    }
}

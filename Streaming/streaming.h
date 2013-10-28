#ifndef STREAMING_H
#define STREAMING_H

#include <QWidget>

#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>

namespace Ui {
class Streaming;
}

class Streaming : public QWidget
{
    Q_OBJECT
    
public:
    explicit Streaming(QWidget *parent = 0);
    ~Streaming();

private slots:
    bool openUrl();
    
    void on_play_button_toggled(bool checked);

private:
    Ui::Streaming *ui;

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
};

#endif // STREAMING_H

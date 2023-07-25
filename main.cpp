#include <QApplication>
#include <QPushButton>
#include <QtGui/QtGui>
//
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QFileDialog>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    //GUI
    QWidget playerWindow;
    QVBoxLayout vbox(&playerWindow);
    QHBoxLayout buttons;
    //video
    auto videoWidget = new QVideoWidget(&playerWindow);
    vbox.addWidget(videoWidget);

    QSlider *songSlider = new  QSlider(&playerWindow);
    songSlider->setOrientation(Qt::Horizontal);
    vbox.addWidget(songSlider);

    auto *openFileButton = new QPushButton("Open", &playerWindow);
    auto *playMediaButton = new QPushButton("Play", &playerWindow);
    auto *pauseMediaButton = new QPushButton("Pause", &playerWindow);

    buttons.addWidget(openFileButton);
    buttons.addWidget(playMediaButton);
    buttons.addWidget(pauseMediaButton);

    vbox.addLayout(&buttons);

    //
    QString filePath;

    auto *player = new QMediaPlayer(&playerWindow);

    player->setVideoOutput(videoWidget);
    bool isPlaying = false;

    QObject::connect(openFileButton, &QPushButton:: clicked, [&filePath, player, &isPlaying]
    {
        filePath = QFileDialog::getOpenFileName(nullptr,
                                     "Open media",
                                     "/Users/gasoline/Downloads/",
                                     "Media mp3 files(*mp3, *.mp4)");
        player->stop();
        isPlaying = false;
    });

    QObject::connect(playMediaButton, &QPushButton::clicked, [&isPlaying, songSlider, player, &filePath]()
{
        if(!isPlaying)
        {
            player->setMedia(QUrl::fromLocalFile(filePath));
            player->setVolume(75);
            QObject::connect(player, &QMediaPlayer::durationChanged, [songSlider](qint64 duration)
            {
                songSlider->setMinimum(0);
                songSlider->setMaximum(duration);
            });

            QObject::connect(player, &QMediaPlayer::positionChanged, [songSlider](qint64 pos)
            {
               songSlider->setValue(pos);
            });
            isPlaying = true;
        }
        player->play();
});


    QObject::connect(songSlider, &QSlider::valueChanged, player, &QMediaPlayer::setPosition);
    QObject::connect(pauseMediaButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    playerWindow.show();


    return app.exec();
}

#include <main.moc>

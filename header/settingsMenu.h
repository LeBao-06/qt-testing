#pragma once

#include "svgbutton.h"
#include "utilities.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QSlider>
#include <QListWidget>
#include <QDir>
#include <QFileInfo>
#include <QMap>


class SettingsMenu : public QGraphicsScene {
    Q_OBJECT

public:
    SettingsMenu(QObject* parent = nullptr);
    ~SettingsMenu();
    float musicVolume = 0.5f, soundEffectVolume = 1.0f;

signals:
    void backActivated();
    void soundEffectVolumeChanged();

private slots:
    void changeMusic(QListWidgetItem*);
    void updateVolume(int);

private:
    QString pathMusic;
    QGraphicsTextItem* txtSettings, * txtMusic, * txtSoundEffect;
    QSlider* backgroundMusicSlider, * soundEffectSlider;
    SvgButton* btnBack;
    QMap<QString, QMediaPlayer*> soundEffects;
    QMap<QString, QAudioOutput*> audioOutputs;

    QGraphicsProxyWidget *listMusicProxy;
    QListWidget listMusic;
    QMediaPlayer* createMediaPlayer(const QString&);
    void initListMusic(const QString &path);
};

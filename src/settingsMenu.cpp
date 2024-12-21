#include "../header/settingsMenu.h"
#include <QDebug>
#include <QTimer>

SettingsMenu::SettingsMenu(QObject* parent):
    QGraphicsScene(parent),
    txtSettings(nullptr),
    txtSoundEffect(nullptr),
    txtMusic(nullptr),
    soundEffectSlider(nullptr),
    backgroundMusicSlider(nullptr),
    btnBack(nullptr)
{
    setSceneRect(0, 0, 1000, 600);
    setBackgroundBrush(QBrush(QColor(59, 66, 82)));
    // setBackgroundBrush(QBrush(QColor("#3B4252")));

    txtSettings = new QGraphicsTextItem("SETTINGS");
    txtSettings->setFont(QFont("Arial", 40, QFont::Bold));
    txtSettings->setDefaultTextColor(Qt::white);
    txtSettings->setPos(500 - txtSettings->boundingRect().width() / 2, 30);
    addItem(txtSettings);

    txtSoundEffect = new QGraphicsTextItem("Sound Effect");
    txtSoundEffect->setFont(QFont("Arial", 14, QFont::Bold));
    txtSoundEffect->setDefaultTextColor(Qt::white);
    txtSoundEffect->setPos(70, 150);
    addItem(txtSoundEffect);

    txtMusic = new QGraphicsTextItem("Music");
    txtMusic->setFont(QFont("Arial", 14, QFont::Bold));
    txtMusic->setDefaultTextColor(Qt::white);
    txtMusic->setPos(70, 200);
    addItem(txtMusic);

    soundEffectSlider = new QSlider(Qt::Horizontal);
    soundEffectSlider->setRange(0, 100);
    soundEffectSlider->setValue(100);
    soundEffectSlider->setGeometry(250, 150, 300, 20);
    addWidget(soundEffectSlider);
    connect(soundEffectSlider, &QSlider::valueChanged, this, [this](int value) {
        soundEffectVolume = value / 100.0;
        volumeEffect = soundEffectVolume;
        emit soundEffectVolumeChanged();
    });

    backgroundMusicSlider = new QSlider(Qt::Horizontal);
    backgroundMusicSlider->setRange(0, 100);
    backgroundMusicSlider->setValue(50);
    backgroundMusicSlider->setGeometry(250, 200, 300, 20);
    addWidget(backgroundMusicSlider);
    connect(backgroundMusicSlider, &QSlider::valueChanged, this, &SettingsMenu::updateVolume);

    soundEffectSlider->setStyleSheet(R"(
        QSlider {
            background: transparent;
        }
        QSlider::groove:horizontal {
            border: 1px solid #bbb;
            background: #eee;
            height: 10px;
            border-radius: 4px;
        }
        QSlider::handle:horizontal {
            background: #3498db;
            border: 1px solid #5c5c5c;
            width: 20px;
            height: 20px;
            margin: -5px 0;
            border-radius: 10px;
        }
        QSlider::handle:horizontal:hover {
            background: #1abc9c;
        }
        QSlider::sub-page:horizontal {
            background: #66ccff;
            border: 1px solid #4a4a4a;
            height: 10px;
            border-radius: 4px;
        }
        QSlider::add-page:horizontal {
            background: #ccc;
            border: 1px solid #4a4a4a;
            height: 10px;
            border-radius: 4px;
        }
    )");

    backgroundMusicSlider->setStyleSheet(R"(
        QSlider {
            background: transparent;
        }
        QSlider::groove:horizontal {
            border: 1px solid #bbb;
            background: #eee;
            height: 10px;
            border-radius: 4px;
        }
        QSlider::handle:horizontal {
            background: #3498db;
            border: 1px solid #5c5c5c;
            width: 20px;
            height: 20px;
            margin: -5px 0;
            border-radius: 10px;
        }
        QSlider::handle:horizontal:hover {
            background: #1abc9c;
        }
        QSlider::sub-page:horizontal {
            background: #66ccff;
            border: 1px solid #4a4a4a;
            height: 10px;
            border-radius: 4px;
        }
        QSlider::add-page:horizontal {
            background: #ccc;
            border: 1px solid #4a4a4a;
            height: 10px;
            border-radius: 4px;
        }
    )");

    btnBack = new SvgButton(":/assets/buttons/back.svg");
    btnBack->fixSize(50);
    btnBack->setPos(10, 10);
    addItem(btnBack);
    connect(btnBack, &SvgButton::clicked, this, [this]() {
        emit backActivated();
    });

    listMusic.setGeometry(70, 250, 480, 300);
    listMusic.resize(480, 300);
    listMusic.setFont(QFont("Courier New", 16));
    listMusic.setFocusPolicy(Qt::NoFocus);
    listMusic.setStyleSheet(
        "QListWidget {"
        "   background: transparent;"
        "   border: 2px solid #8a2be2;"
        "   border-radius: 15px;"
        "   padding: 5px;"
        "   font: bold 14px 'Arial';"
        "}"
        "QListWidget::item {"
        "   color: #4b0082;"
        "   background: #e6e6fa;"
        "   margin: 5px;"
        "   padding: 10px;"
        "   border-radius: 10px;"
        "}"
        "QListWidget::item:selected {"
        "   background: #8a2be2;"
        "   color: white;"
        "}"
        "QListWidget::item:hover {"
        "   background: #d8bfd8;"
        "}"
    );
    addWidget(&listMusic);


    QDir dir(QCoreApplication::applicationDirPath());
    while (!dir.exists("assets")) {
        if (!dir.cdUp()) {
            // Nếu không thể cdUp() thêm nữa, thoát khỏi vòng lặp
            //qDebug() << "Folder 'savefiles' không tồn tại trong bất kỳ thư mục cha nào.";
            break;
        }
    }
    pathMusic = dir.absolutePath() + "/assets/backgroundmusic/";
    initListMusic(pathMusic);
    connect(&listMusic, &QListWidget::itemClicked, this, &SettingsMenu::changeMusic);

    if (listMusic.count() > 0) {
        QListWidgetItem* firstItem = listMusic.item(0);
        listMusic.setCurrentItem(firstItem); // Đặt phần tử đầu tiên được chọn
        changeMusic(firstItem);             // Phát nhạc tương ứng
    }

}

QMediaPlayer* SettingsMenu::createMediaPlayer(const QString &filePath) {
    QMediaPlayer* player = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(musicVolume);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl(pathMusic+ filePath));
    player->setLoops(QMediaPlayer::Infinite);
    audioOutputs[filePath] = audioOutput;
    return player;
}

void SettingsMenu::initListMusic(const QString& path) {
    QDir dir(path);
    QStringList files = dir.entryList(QDir::Files);
    for (const QString& file : files) {
        QListWidgetItem* item = new QListWidgetItem(file);
        QString text = item->text();
        if(text.endsWith(".mp3")){
            text.chop(4);
            soundEffects[text] = createMediaPlayer(text + ".mp3");
            item->setText(text);
        }
        listMusic.addItem(item);
    }
}

void SettingsMenu::changeMusic(QListWidgetItem *item) {
    for (auto *player : soundEffects) {
        player->stop();
    }
    if (soundEffects.contains(item->text())) {
        soundEffects[item->text()]->play();
    }
}

void SettingsMenu::updateVolume(int value) {
    musicVolume = value/100.f;
    //qDebug() << value;
    for (auto *audioOutput : audioOutputs) {
        audioOutput->setVolume(musicVolume);
    }
}

SettingsMenu::~SettingsMenu() {
    // Delete dynamically allocated QGraphicsTextItems
    delete txtSettings;
    delete txtMusic;
    delete txtSoundEffect;

    // Delete dynamically allocated sliders
    delete backgroundMusicSlider;
    delete soundEffectSlider;

    // Delete dynamically allocated SvgButton
    delete btnBack;

    // Delete all QMediaPlayer and QAudioOutput objects in QMaps
    for (auto mediaPlayer : soundEffects) {
        delete mediaPlayer;
    }
    for (auto audioOutput : audioOutputs) {
        delete audioOutput;
    }

    // Clear the QMaps
    soundEffects.clear();
    audioOutputs.clear();

    // Delete the QGraphicsProxyWidget
    delete listMusicProxy;

    // Clear the music list if necessary
    listMusic.clear();
}

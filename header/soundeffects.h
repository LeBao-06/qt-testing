#pragma once

#include "chess.hpp"
#include <QtMultimedia/QSoundEffect>
#include <QCoreApplication>

class SoundEffect {
public:
    SoundEffect();
    ~SoundEffect(void);
    void soundMoveSelf(void);
    void soundPromote(void);
    void soundCapture(void);
    void soundMoveCheck(void);
    void soundCastling(void);
    void soundWinGame(void);
    void soundDrawGame(void);
    void resetVolume(float volume);
    float volume = 1.0f;

private:
    QSoundEffect moveSelfSound;
    QSoundEffect promoteSound;
    QSoundEffect captureSound;
    QSoundEffect moveCheckSound;
	QSoundEffect castlingSound;
    QSoundEffect gameWinSound, gameDrawSound;
};

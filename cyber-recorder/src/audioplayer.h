/*
 * SPDX-FileCopyrightText: 2020 Devin Lin <espidev@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMediaPlayer>
#include <QAudioProbe>
#include <QQmlEngine>
#include <QUrl>
#include <QCoreApplication>

#include "audioprober.h"

class AudioPlayer;
static AudioPlayer *s_audioPlayer = nullptr;

class AudioPlayer : public QMediaPlayer
{
    Q_OBJECT
    Q_PROPERTY(AudioProber *prober READ prober CONSTANT)
    Q_PROPERTY(QString mediaPath READ mediaPath WRITE setMediaPath NOTIFY mediaPathChanged)

public:
    static AudioPlayer *instance()
    {
        if (!s_audioPlayer) {
            s_audioPlayer = new AudioPlayer(qApp);
        }
        return s_audioPlayer;
    }

    void handleStateChange(QMediaPlayer::State state);

    AudioProber *prober()
    {
        return m_audioProbe;
    }

    Q_INVOKABLE void setMediaPath(QString path)
    {
        m_mediaPath = path;
        setMedia(QUrl::fromLocalFile(path));
    }

    QString mediaPath() const
    {
        return m_mediaPath;
    }

signals:
    void mediaPathChanged();

private:
    explicit AudioPlayer(QObject *parent = nullptr);

    AudioProber *m_audioProbe;
    QString m_mediaPath;
    
    bool wasStopped = false;
};

#endif

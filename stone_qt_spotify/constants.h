#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QByteArray>
#include <QUrl>

namespace Constants {
    const QByteArray SPOTIFY_CLIENT_ID = "3ff6b6c79d82413eaedf750799c4075d";
    const QByteArray SPOTIFY_CLIENT_SECRET = "8e28a26e9f4d4c179b73d798df722f79";

    const QUrl SPOTIFY_AUTHORIZATION_URL = QUrl("https://accounts.spotify.com/authorize");
    const QUrl SPOTIFY_ACCESSTOKEN_URL = QUrl("https://accounts.spotify.com/api/token");

    const QUrl SPOTIFY_GET_ME = QUrl("https://api.spotify.com/v1/me");

    const QString SPOTIFY_TRACK_SEARCH = QString("https://api.spotify.com/v1/search?q=track:%1&type=track&limit=50");
}

#endif // CONSTANTS_H

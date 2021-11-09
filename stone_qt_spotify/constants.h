#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QByteArray>
#include <QUrl>

namespace Constants {
    const QByteArray SPOTIFY_CLIENT_ID = "3ff6b6c79d82413eaedf750799c4075d";
    const QByteArray SPOTIFY_CLIENT_SECRET = "615a644b3a1b4d6aad54d9d3dd66b195";

    const QUrl SPOTIFY_AUTHORIZATION_URL = QUrl("https://accounts.spotify.com/authorize");
    const QUrl SPOTIFY_ACCESSTOKEN_URL = QUrl("https://accounts.spotify.com/api/token");
}

#endif // CONSTANTS_H

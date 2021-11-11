#ifndef SPOTIFYWRAPPER_H
#define SPOTIFYWRAPPER_H

#include "spotifytrack.h"
#include "constants.h"

#include <QOAuth2AuthorizationCodeFlow>
#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class SpotifyWrapper : public SpotifyTrack
{
    Q_OBJECT
public:
    SpotifyWrapper();
    //Get data from the user logged
    void GetUser(void);
    //Get Image from URL
    void GetImg(QString sUrl);

public Q_SLOTS:

    //Connect and Authenticate
    void Grant(void);

Q_SIGNALS:
    void Authenticated(void);
    void SendUser(QString str);
    void SendImg(QByteArray jpegData);

protected:
    QOAuth2AuthorizationCodeFlow oauth2;
};

#endif // SPOTIFYWRAPPER_H

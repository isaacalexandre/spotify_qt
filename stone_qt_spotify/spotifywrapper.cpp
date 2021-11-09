#include "spotifywrapper.h"
#include "networkaccessmanager.h"
#include "constants.h"

#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>


SpotifyWrapper::SpotifyWrapper(QObject *parent) : QObject(parent)
{
    QOAuthHttpServerReplyHandler * replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    replyHandler->setCallbackPath("callback");
    oauth2.setNetworkAccessManager(new NetworkAccessManager(this));
    oauth2.setReplyHandler(replyHandler);
    oauth2.setAuthorizationUrl(Constants::SPOTIFY_AUTHORIZATION_URL);
    oauth2.setAccessTokenUrl(Constants::SPOTIFY_ACCESSTOKEN_URL);
    oauth2.setClientIdentifier(Constants::SPOTIFY_CLIENT_ID);
    oauth2.setScope("user-read-private user-read-email");
    oauth2.setState("34fFs29kd09");
    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
        if (status == QAbstractOAuth::Status::Granted){
            emit authenticated();
        }
    });
}

void SpotifyWrapper::grant()
{
    oauth2.grant();
}

void SpotifyWrapper::GetUser(void)
{
    //Sanity
    if (oauth2.status() != QAbstractOAuth::Status::Granted) {
        return;
    }

    QNetworkReply * aux_reply = oauth2.get(QUrl("https://api.spotify.com/v1/me"));    
    connect(aux_reply, &QNetworkReply::finished, [=]() {
        aux_reply->deleteLater();
        if (aux_reply->error() == QNetworkReply::NoError) {

            const auto json = aux_reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(json);
            Q_ASSERT(jsonDocument.isObject());
            QJsonObject object = jsonDocument.object();

            emit sendUser(object.value("display_name").toString());
        }
    });
}

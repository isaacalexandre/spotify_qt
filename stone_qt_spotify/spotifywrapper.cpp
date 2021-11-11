#include "spotifywrapper.h"
#include "networkaccessmanager.h"

SpotifyWrapper::SpotifyWrapper() : SpotifyTrack(&oauth2)
{
    //Set Handles and configure OAuth2
    QOAuthHttpServerReplyHandler * replyHandler = new QOAuthHttpServerReplyHandler(1337, this); //1337 is the port was configurated in the Spotify Dashboard
    replyHandler->setCallbackPath("callback");
    oauth2.setNetworkAccessManager(new NetworkAccessManager(this));
    oauth2.setReplyHandler(replyHandler);
    oauth2.setAuthorizationUrl(Constants::SPOTIFY_AUTHORIZATION_URL);
    oauth2.setAccessTokenUrl(Constants::SPOTIFY_ACCESSTOKEN_URL);
    oauth2.setClientIdentifier(Constants::SPOTIFY_CLIENT_ID);
    oauth2.setScope("user-read-private user-read-email");
    oauth2.setState("34fFs29kd09");
    //
    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
        if (status == QAbstractOAuth::Status::Granted){
            emit Authenticated();
        }
    });
}

//Connect and Authenticate
void SpotifyWrapper::Grant()
{
    oauth2.grant();
}

//Get data from the user logged
void SpotifyWrapper::GetUser(void)
{
    //Sanity
    if (oauth2.status() != QAbstractOAuth::Status::Granted) {
        return;
    }

    QNetworkReply * aux_reply = oauth2.get(Constants::SPOTIFY_GET_ME);
    connect(aux_reply, &QNetworkReply::finished, [=]() {
        aux_reply->deleteLater();
        if (aux_reply->error() == QNetworkReply::NoError) {

            QByteArray json = aux_reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(json);
            Q_ASSERT(jsonDocument.isObject());
            QJsonObject object = jsonDocument.object();

            emit SendUser(object.value("display_name").toString());
        }
    });
}

//Get Image from URL
void SpotifyWrapper::GetImg(QString sUrl)
{
    //Sanity
    if (oauth2.status() != QAbstractOAuth::Status::Granted) {
        return;
    }

    QNetworkReply * aux_reply = oauth2.get(QUrl(sUrl));
    connect(aux_reply, &QNetworkReply::finished, [=]() {
        aux_reply->deleteLater();
        if (aux_reply->error() == QNetworkReply::NoError) {
            emit SendImg(aux_reply->readAll());
        }
    });
}

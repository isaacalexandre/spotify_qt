#include "spotifytrack.h"

#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

SpotifyTrack::SpotifyTrack(QOAuth2AuthorizationCodeFlow* oauth2)
{
    //Set the pointer
    p_oauth2 = oauth2;
}

//Return from the vector the track data
SpotifyTrack::TrackStruct SpotifyTrack::GetTrack(int idx)
{
    SpotifyTrack::TrackStruct track_aux;

    //Sanity
    if(idx < vec_tracks.size())
        track_aux = vec_tracks.at(idx);

    return track_aux;
}

//Search in Spotify API Tracks
void SpotifyTrack::SearchTrack(QString str)
{
    //Sanity
    if (p_oauth2->status() != QAbstractOAuth::Status::Granted) {
        return;
    }

    //Clear the vector before fill with new data
    vec_tracks.clear();

    QNetworkReply * aux_reply = p_oauth2->get(QUrl(Constants::SPOTIFY_TRACK_SEARCH.arg(str)));
    connect(aux_reply, &QNetworkReply::finished, [=]() {
        QJsonArray::iterator it;
        aux_reply->deleteLater();

        if (aux_reply->error() == QNetworkReply::NoError) {
            //Get all data
            QByteArray json = aux_reply->readAll();
            //Convert to JSON obj
            QJsonDocument jsonDocument = QJsonDocument::fromJson(json);
            Q_ASSERT(jsonDocument.isObject());
            QJsonObject root = jsonDocument.object();
            Q_ASSERT(root.value("tracks").isObject());
            QJsonObject tracks_json = root.value("tracks").toObject();
            //Verify if is a array and put to the variable
            Q_ASSERT(tracks_json.value("items").isArray());
            QJsonArray items = tracks_json.value("items").toArray();

            //Populate the vector
            for(it = items.begin(); it != items.end(); it++){
                TrackStruct ts_aux;
                QJsonObject track_selec = it->toObject();
                ts_aux.name = track_selec.value("name").toString();
                ts_aux.url_sample = track_selec.value("preview_url").toString();
                ts_aux.id_track = track_selec.value("id").toString();
                ts_aux.album = track_selec.value("album").toObject().value("name").toString();
                ts_aux.album_image = track_selec.value("album").toObject().value("images").toArray().at(0).toObject().value("url").toString(); //Sorry :D
                ts_aux.artist = track_selec.value("artists").toArray().at(0).toObject().value("name").toString();
                //Add to the vector
                vec_tracks.append(ts_aux);
            }
            //Send the signal
            emit SendTrack(&vec_tracks);
        }
    });
    return;
}

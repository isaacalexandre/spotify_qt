#ifndef SPOTIFYTRACK_H
#define SPOTIFYTRACK_H
#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include "constants.h"

class SpotifyTrack : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyTrack(QOAuth2AuthorizationCodeFlow* oauth2);

    //Struct to storage
    class TrackStruct
    {
        public:
            QString name;
            QString artist;
            QString album;
            QString album_image;
            QString url_sample;
            QString id_track;
    };
    //Search in Spotify API Tracks
    void SearchTrack(QString str);
    //Return from the vector the track data
    TrackStruct GetTrack(int idx);

private:
    //Pointer to NewtorkManager+OAuth2
    QOAuth2AuthorizationCodeFlow* p_oauth2;
    //Struct to storage the tracks searched
    QVector<TrackStruct> vec_tracks;

public Q_SLOTS:


Q_SIGNALS:
    void SendTrack(QVector<TrackStruct>* vec);

};

#endif // SPOTIFYTRACK_H

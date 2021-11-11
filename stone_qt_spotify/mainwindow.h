#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spotifywrapper.h"

#include <QNetworkReply>
#include <QGuiApplication>
#include <QObject>
#include <QListWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Event to connect and authenticate
    void on_AuthPushButton_clicked();
    //Start the track search
    void on_SearchPushButton_clicked();
    //Set in the UI the User and show is connected
    void SetConnected();
    //Set in the UI the User and show is connected
    void SetUser(QString Str);
    //Show in the UI the track list searched
    void SetTracks(QVector<SpotifyTrack::TrackStruct>* vec);
    //Receive the image requested by URL
    void SetImg(QByteArray jpegData);
    //Get the tracj from track and add to offline playlist
    void AddToPlaylist(int idx);
    //Update Data from the vector to the widget
    void UpdatePlaylistList(void);
    //Update Labels Preview
    void UpdatePreview(SpotifyTrack::TrackStruct track);
    //Verify if the track is already in the vector playlist
    bool IsRepeatTrack(QString id_track);
    //Double click to add to playslit
    void on_TrackListWidget_itemDoubleClicked(QListWidgetItem *item);
    //Add track to plasylist
    void on_AddTrackPushButton_clicked();
    //Remove track from playlist
    void on_RemovePushButton_clicked();
    //Update the preview track
    void on_TrackListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    //Update the preview playlist
    void on_PlaylistListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    //Event to play sample
    void on_PlayPushButton_clicked();
    //Event to play sample
    void on_PlaylistListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    SpotifyWrapper* spotify;
    //Pointer to get specific track
    SpotifyTrack* track;
    //Vector to storage the playlist offline
    QVector<SpotifyTrack::TrackStruct> vec_playlist;
    //Pointer to get the searched tracks
    QVector<SpotifyTrack::TrackStruct>* vec_search;
};
#endif // MAINWINDOW_H

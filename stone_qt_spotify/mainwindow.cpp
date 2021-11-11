#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Set to invisible the preview
    ui->PreviewGroupBox->setVisible(false);
    //Set the string max length
    ui->SearchLineEdit->setMaxLength(30);
    //Block Drag and Drops
    ui->PlaylistListWidget->setAcceptDrops(false);
    ui->PlaylistListWidget->setDragEnabled(false);
    ui->TrackListWidget->setAcceptDrops(false);
    ui->TrackListWidget->setDragEnabled(false);
    //Init the class Spotify
    spotify = new SpotifyWrapper();
    //Wrapper
    QObject::connect(spotify, &SpotifyWrapper::Authenticated, this, &MainWindow::SetConnected);
    QObject::connect(spotify, &SpotifyWrapper::SendUser, this, &MainWindow::SetUser);
    //Tracks
    QObject::connect(spotify, &SpotifyWrapper::SendTrack, this, &MainWindow::SetTracks);
    //Img
    QObject::connect(spotify, &SpotifyWrapper::SendImg, this, &MainWindow::SetImg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slots ----------------------------------------------

//Set in the UI the User and show is connected
void MainWindow::SetConnected()
{
    ui->StatusLabel->setText("Conectado");
    ui->AuthPushButton->setEnabled(false);
    ui->SearchGroupBox->setEnabled(true);
    ui->PlaylistGroupBox->setEnabled(true);
    spotify->GetUser();
}

//Set in the UI the User and show is connected
void MainWindow::SetUser(QString Str)
{
    ui->UserLabel->setText(Str);
}

//Show in the UI the track list searched
void MainWindow::SetTracks(QVector<SpotifyTrack::TrackStruct>* vec)
{
    QVector<SpotifyTrack::TrackStruct>::iterator it;
    //Populate the UI Widget
    if(vec != NULL){
        ui->TrackListWidget->clear();
        for(it = vec->begin(); it != vec->end(); it++){
            ui->TrackListWidget->addItem(it->name + ", " + it->artist);
        }
    }
}

//Receive the image requested by URL
void MainWindow::SetImg(QByteArray jpegData)
{
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    ui->imgLabel->setPixmap(pixmap);
}

//Update Preview
void MainWindow::UpdatePreview(SpotifyTrack::TrackStruct track)
{
    ui->PreviewGroupBox->setVisible(true);
    ui->EditTrackLabel->setText(track.name);
    ui->EditArtistLabel->setText(track.artist);
    ui->EditAlbumLabel->setText(track.album);
}

//Verify if the track is already in the vector playlist
bool MainWindow::IsRepeatTrack(QString id_track)
{
    QVector<SpotifyTrack::TrackStruct>::iterator it;
    for(it = vec_playlist.begin(); it != vec_playlist.end(); it++){
        if(it->id_track == id_track)
            return true;
    }
    return false;
}

//Get the tracj from track and add to offline playlist
void MainWindow::AddToPlaylist(int idx)
{
    SpotifyTrack::TrackStruct aux_track = spotify->GetTrack(idx);
    //Verify if the track already has added
    if(!IsRepeatTrack(aux_track.id_track)){
        //Get from SpotifyTrack the track selected
        vec_playlist.append(aux_track);
        UpdatePlaylistList();
    }
}

//Update Data from the vector to the widget
void MainWindow::UpdatePlaylistList(void)
{
    QVector<SpotifyTrack::TrackStruct>::iterator it;
    //Clear before populate
    ui->PlaylistListWidget->clear();
    for(it = vec_playlist.begin(); it != vec_playlist.end(); it++) {
        ui->PlaylistListWidget->addItem(it->name + ", " + it->artist);
    }
}


// Events ----------------------------------------------

//Event to connect and authenticate
void MainWindow::on_AuthPushButton_clicked()
{
    //Conect and Authenticate
    spotify->Grant();
}

//Start the track search
void MainWindow::on_SearchPushButton_clicked()
{
    //Search the tracks
    if(ui->SearchLineEdit->text().length() != 0)
        spotify->SearchTrack(ui->SearchLineEdit->text());
}

//Double click to add to playslit
void MainWindow::on_TrackListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //Send to list the selected track
    AddToPlaylist(ui->TrackListWidget->row(item));
}

//Update the preview track
void MainWindow::on_TrackListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(current){
        SpotifyTrack::TrackStruct aux_track = spotify->GetTrack(ui->TrackListWidget->row(current));
        spotify->GetImg(aux_track.album_image);
        UpdatePreview(aux_track);
    }
}

//Update the preview playlist
void MainWindow::on_PlaylistListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);
    //Sanity
    if(ui->PlaylistListWidget->row(current) < vec_playlist.size() && current){
        SpotifyTrack::TrackStruct aux_track = vec_playlist.at(ui->PlaylistListWidget->row(current));
        spotify->GetImg(aux_track.album_image);
        UpdatePreview(aux_track);
    }
}

//Add track to plasylist
void MainWindow::on_AddTrackPushButton_clicked()
{
    //Send to list the selected track
    if(ui->TrackListWidget->currentItem() != NULL)
        AddToPlaylist(ui->TrackListWidget->row(ui->TrackListWidget->currentItem()));
}

//Remove track from playlist
void MainWindow::on_RemovePushButton_clicked()
{
    int idx = 0;
    //Remove from list the selected track
    if(ui->PlaylistListWidget->currentItem() != NULL) {
        idx = ui->PlaylistListWidget->row(ui->PlaylistListWidget->currentItem());
        //Sanity
        if(idx < vec_playlist.size()) {
            //Remove from the vector and update the list
            vec_playlist.remove(idx,1);
            UpdatePlaylistList();
        }
    }
}

//PlaySong
void MainWindow::on_PlayPushButton_clicked()
{
    int idx = 0;
    //Send to list the selected track
    if(ui->PlaylistListWidget->currentItem() != NULL) {
        idx = ui->PlaylistListWidget->row(ui->PlaylistListWidget->currentItem());
        //Sanity
        if(idx < vec_playlist.size()) {
            //Open Sample in the browser
            QDesktopServices::openUrl(QUrl(vec_playlist.at(idx).url_sample));
        }
    }
}

//PlaySong
void MainWindow::on_PlaylistListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int idx = ui->PlaylistListWidget->row(item);
    if(idx < vec_playlist.size()) {
        //Open Sample in the browser
        QDesktopServices::openUrl(QUrl(vec_playlist.at(idx).url_sample));
    }
}


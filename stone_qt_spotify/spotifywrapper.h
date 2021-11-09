#ifndef SPOTIFYWRAPPER_H
#define SPOTIFYWRAPPER_H

#include <QOAuth2AuthorizationCodeFlow>
#include <QObject>

class SpotifyWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyWrapper(QObject *parent = nullptr);
    void GetUser(void);
public Q_SLOTS:
    void grant(void);
Q_SIGNALS:
    void authenticated(void);
    void sendUser(QString str);
private:
    QOAuth2AuthorizationCodeFlow oauth2;
};

#endif // SPOTIFYWRAPPER_H

#ifndef HANDLER_H
#define HANDLER_H
#include <QString>
#include <QObject>

class Worker;
class Handler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString vfile READ vfile WRITE setVfile NOTIFY vfileChanged)
    Q_PROPERTY(QString vfolder READ vfolder WRITE setVfolder NOTIFY vfolderChanged)
    Q_PROPERTY(int sochu READ sochu NOTIFY sochuChanged)
    Q_PROPERTY(int sokitu READ sokitu NOTIFY sokituChanged)
    Q_PROPERTY(QString giong READ giong WRITE setgiong NOTIFY giongChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(QString mediafile READ mediafile NOTIFY mediafileChanged)
public:
    Handler(QObject *parent= nullptr);
    virtual ~Handler();

    Q_INVOKABLE void getDataStart(QString const &data, bool isTextbox = true);
    Q_INVOKABLE void playMediaFile(const QString path);

    Q_INVOKABLE QString getpath(QString path);
    QString vfile() const;
    QString vfolder() const;
    void setVfile(QString file);
    void setVfolder(QString folder);

    QString mediafile();
    void setMediafile(QString str);
    int sochu()const;
    int sokitu()const;
    QString giong() const;
    void setgiong(QString giong);
    QString getGiong();
    QString createNameFile();
    int progress() const;
    void updateprogress(int val);
    void timerEvent(QTimerEvent *event);
    void init();
    void end();
private:
    int m_init{0};
    QString pathFile;
    QString pathFolder;
    uint64_t m_sochu,m_sokitu;
    QString m_giong;
    int m_fprogress;
    int timerID;
    QString m_mediafile;
    bool m_state{false};
//    QMediaPlayer *player;
signals:
    void vfileChanged();
    void vfolderChanged();
    void updateinfokitu();
    void sochuChanged();
    void sokituChanged();
    void giongChanged();
    void progressChanged();
    void mediafileChanged();
};


#endif // HANDLER_H

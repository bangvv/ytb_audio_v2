#include "Handler.h"
#include "Worker.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

Handler::Handler(QObject *parent):QObject(parent),
    pathFile{""},m_giong{"nam_01"},m_fprogress{0},
    pathFolder{""},m_sochu{0},m_sokitu{0}
{
    timerID = startTimer(300);
//    init();
//    player = new QMediaPlayer();
}

Handler::~Handler()
{
    killTimer(timerID);
    end();
}

void Handler::getDataStart(const QString &data,bool isTextbox)
{
    updateprogress(0);
    QString Text;
    QString Name;
    bool isready = false;
    if(isTextbox && !data.isEmpty())
    {
        Text = data;
        isready = true;
        Name = "TTS_AmThanh";
    }
    else if(!isTextbox)
    {
        if(!pathFile.isEmpty()){
            QFile FILE(pathFile);
            if (FILE.open(QIODevice::ReadOnly))
            {
                Text = QString(FILE.readAll());
                FILE.close();
                isready = true;
            }
        }
        Name = createNameFile();
    }
    if (isready){
        m_sochu = Text.split(" ").size();
        m_sokitu = Text.length();
        Worker& w = Worker::getInstance();
        w.SetGiongDataBase(getGiong());
        w.setNameWav(createNameFile());
        w.threadWorkerwav(Text);
        emit sochuChanged();
    }
}

void Handler::playMediaFile(const QString path)
{

}

QString Handler::getpath(QString path)
{
    QString ret;
    if (path.mid(path.length()-4) == ".txt"){
        int pos = 0;
        for(int i = path.length(); i > 0; i--)
        {
            if (path[i] == '/'){
                pos = i;
                break;
            }
        }
        ret = path.mid(0,pos);
        return ret;
    }
    return "";
}

QString Handler::vfile() const
{
    return pathFile;
}

QString Handler::vfolder() const
{
    return pathFolder;
}

void Handler::setVfile(QString vfile)
{
    if (vfile.contains("file:///"))
        vfile = vfile.replace("file:///","");
    pathFile = vfile;
    emit vfileChanged();
}

void Handler::setVfolder(QString folder)
{
    if (folder.contains("file:///"))
        folder = folder.replace("file:///","");
    pathFolder = folder;
    emit vfolderChanged();
}

QString Handler::mediafile()
{
    return m_mediafile;
}

void Handler::setMediafile(QString str)
{
    if (!str.isEmpty()){
        m_mediafile = "file:///" + str;
        emit mediafileChanged();
    }
}

int Handler::sochu() const
{
    if (m_sochu >INT_MAX)
        return INT_MAX;

    return static_cast<int>(m_sochu);
}

int Handler::sokitu() const
{
    if (m_sokitu >INT_MAX)
        return INT_MAX;

    return static_cast<int>(m_sokitu);
}

QString Handler::giong() const
{
    return m_giong;
}

void Handler::setgiong(QString giong)
{
    m_giong = giong;
    emit giongChanged();
}

QString Handler::getGiong()
{
    return m_giong;
}

QString Handler::createNameFile()
{
    if (pathFile.isEmpty() && pathFolder.isEmpty())
        return "";

    QString path = pathFile;
    QString namefile;
    if (path.mid(path.length()-4) == ".txt"){
        int pos = 0;
        for(int i = path.length(); i > 0; i--)
        {
            if (path[i] == '/'){
                pos = i;
                break;
            }
        }
        namefile = path.mid(pos,path.length()-pos - 4);
    }
    QString name (pathFolder+ '/' + namefile);
    return name;
}
void Handler::init()
{
    QFile setting("setting.json");
    if (setting.open(QIODevice::ReadOnly| QIODevice::Text)){
        QByteArray buff = setting.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(buff);
        QJsonObject object = doc.object();
        if(object.contains("GIONG") && object.contains("pathFile") && object.contains("pathFolder")){
           m_giong = (object["GIONG"].toString());
           setVfile(object["pathFile"].toString());
           setVfolder(object["pathFolder"].toString());
        }
        setting.close();
    }
}
void Handler::end(){
    QFile setting("setting.json");
    if (setting.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)){
        QByteArray buff = setting.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(buff);
        QJsonObject object = doc.object();
        object["GIONG"] = m_giong;
        object["pathFile"] = pathFile;
        object["pathFolder"] = pathFolder;
        QJsonDocument docsave(object);
        QByteArray buffsave = docsave.toJson();
        setting.write(buffsave);
        setting.close();
    }
}
int Handler::progress() const
{
    return m_fprogress;
}

void Handler::updateprogress(int val)
{
    m_fprogress = val;
    emit progressChanged();
}

void Handler::timerEvent(QTimerEvent *event)
{
    Worker& w = Worker::getInstance();
    updateprogress(w.getProgress());
    if (m_init < 3){
        init();
        m_init++;
    }
//    setMediafile(w.getMediaFile());
}

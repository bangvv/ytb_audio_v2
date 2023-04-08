#include "Worker.h"
#include <functional>
#include <windows.h>
#include <iostream>
#include "DataBase.h"
#include "wav.h"
#include "TextData.h"

extern void chinh(QString& textpos);
bool isSPACE(QString& text);
static char arr[1024];
static char buffd[1024];
QByteArray createBuff(int x = 1024)
{
    memset(arr,0,1024);
    memset(buffd,0,1024);
    arr[40] = 'd';
    arr[41] = 'a';
    arr[42] = 't';
    arr[43] = 'a';
    QByteArray data(arr,1024);
    int size = 1024;
    while(size < x)
    {
        data+=QByteArray(buffd,1024);
        size+=1024;
    }
    return data;
}
Worker::Worker():thread_run{nullptr}
{
    db = new DataBase();
    wav = new Wav();
    text = new TextData();
}
Worker Worker::m_worker;
Worker::~Worker()
{
    cv = false;
    delete db;
    delete wav;
}

Worker& Worker::getInstance()
{
    return m_worker;
}

void Worker::threadWorkerwav(QString& data)
{
    if(thread_run == nullptr)
    {
        //
        // cần c++ 17 trong cmke hoặc qmake để pass thêm tham số
        //
        m_data = data;
        QThread *thread_run1 = QThread::create(RunthreadWorkerwav,this);
        thread_run1->start();
    }
}

void RunthreadWorkerwav(Worker *worker)
{
    QString data = worker->getdata();

    QString giong = worker->getGiong();

    TextData textdata = worker->getTextData();
    textdata.HandlerText(data);
    textdata.UpdateText(data);
    // CHUAN BI DATA
    DataBase db = worker->getDataBase();
    db.setupData(data);
    db.updateListdoi(data);

    Wav wav = worker->getWav();
    //
    QString text;
    QString error;
    QByteArray am;
    bool isspace = false;
    QList<QString> list = data.split(" ",QString::SkipEmptyParts);
    uint size = list.size();
    bool islate = false;
    for (uint i = 0; i < size; i++)
    {
        text = list.at(i);
        if (i == size -1)
            islate = true;

        if (isSPACE(text))
        {
            isspace = true;
        }
        chinh(text);
        if(db.isGhep(text.toLower())){

        }
        else{
            am = db.getDataBase(text.toLower());
            if(i!= 0 && !am.isEmpty()){
                if ("nam_01" == giong)
                    am = wav.HandleNam01(am,text.toLower());
                else if("nu_01" == giong)
                {
                    am = wav.HandleNu01(am,text.toLower());
                }
            }
            else
            {
                if (am.isEmpty())
                    error+=text+" ";
            }
            wav.appendWav(am,false);
        }
        am.clear();
        if (isspace){
            am = createBuff(16*1024);
            wav.appendWav(am,false);
        }
        isspace = false;        
        worker->updateProgress(i*100/size);
    }
    wav.appendWav(am,true);
    worker->updateProgress(100);
    wav.resetInfor();
    textdata.CreateError(error);
}

QString& Worker::getdata()
{
    return m_data;
}
void Worker::initData()
{

}

void Worker::setdk(bool dk)
{
    cv = dk;
}

bool Worker::getdk() const
{
    return cv;
}

DataBase &Worker::getDataBase()
{
    return *db;
}

Wav &Worker::getWav()
{
    return *wav;
}

TextData &Worker::getTextData()
{
    return *text;
}

void Worker::SetGiongDataBase(const QString &str)
{
    giong = str;
    if (db)
        db->setGiongDataBase(str);
}

void Worker::setNameWav(const QString &str)
{
    if (wav)
        wav->SetNameFile(str);
}

int Worker::getProgress()
{
    return progress;
}

void Worker::updateProgress(int value)
{
    progress = value;
}

QString Worker::getMediaFile()
{
    QString ret;
    if (wav)
        ret = wav->GetNameFile();
    return ret;
}

bool Worker::getState()
{
    if (wav)
        return wav->state();
    return false;
}

QString Worker::getGiong()
{
    return giong;
}
bool isSPACE(QString& text){
    return  text.contains(',') || text.contains('.') ||
            text.contains('?') || text.contains('!') ||
            text.contains(':') || text.contains("…") || text.contains(";") ||
             text.contains("~");
}

#ifndef WORKER_H
#define WORKER_H
#include <atomic>
#include <QString>
#include <QThread>

class Wav;
class DataBase;
class TextData;
class Worker
{
private:
    Worker();
    static Worker m_worker;
public:
    ~Worker();
    static Worker& getInstance();

    void threadWorkerwav(QString& data);
    void initData();
    QString& getdata();
    void setdk(bool dk);
    bool getdk()const;
    DataBase& getDataBase();
    Wav& getWav();
    TextData& getTextData();
    void SetGiongDataBase(const QString& str);
    void setNameWav(const QString& str);
    int getProgress();
    void updateProgress(int value);
    QString getMediaFile();
    bool getState();
    QString getGiong();
private:
    QString m_data;
    QThread *thread_run;
    std::atomic_int progress{0};
    std::atomic_bool cv{true};

    QString giong;
    DataBase *db;
    Wav *wav;
    TextData *text;
};

void RunthreadWorkerwav(Worker* worker);

#endif // WORKER_H

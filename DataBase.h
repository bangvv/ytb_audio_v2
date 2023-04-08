#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QList>
#include <QMap>
#include <QPair>
#include <QByteArray>

class DataBase{
public:
    DataBase();
    ~DataBase();
    void loadData();
    void checkData(const QString &str);
    void readsetting();
    void writeSetting();
    void updateFileFolder(const QString& file,const QString& folder);
    void loadMap();
    void loadListghep();
    void AddList(QStringList &list1);
    void checkHead();
    void updateListdoi(QString &);
    void setupData(const QString &);
    bool isGhep(const QString &);
    QByteArray getDataBase(const QString &);
    void setGiongDataBase(const QString& giong);
private:
    void readMap();
    bool isNumber(const QString &);
    QByteArray Data(const QString &textQS);
    QList<QString> m_datas;
    QList<QString> don;
    QList<QString> m_listdoi;
    QList<QString> m_listghep;

    QString pathData;
    QString pathListDoi;
    QString pathGiong;

    QString file,folder;

    QMap <QString,QPair<int,uint>> configmap;
    QMap<QString,QByteArray> map;
    QList<QString> listdatatoiuu;
};

extern void chinh(QString& textpos);
#endif // DATABASE_H

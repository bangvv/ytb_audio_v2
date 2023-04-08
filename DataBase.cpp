#include "DataBase.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <iostream>
#include <QDir>
#include <QTextStream>

void DataBase::loadListghep(){
    QFile filetughep("./conf/listwords.txt");
    if (filetughep.open(QIODevice::ReadOnly))
    {
        QTextStream in(&filetughep);
        in.setCodec("UTF-8");
        while(!in.atEnd()){
             QString line = in.readLine();
             m_listghep.push_back(line);
        }
        filetughep.close();
    }
}

DataBase::DataBase():file(""),folder("")
{
}
DataBase::~DataBase() {}
void DataBase::checkHead()
{

}

void DataBase::updateListdoi(QString &str)
{
    QString data;
    for (uint i = 0; i < m_listghep.size(); i++)
    {
        if(str.contains(m_listghep.at(i))){
            m_listdoi.push_back(m_listghep.at(i));
            data = m_listghep.at(i);
            data = data.replace(' ', '_');
            str = str.replace(m_listghep.at(i),data);
        }
    }
}

void DataBase::setupData(const QString &str)
{
    QString data = str;
    if (!listdatatoiuu.isEmpty())
        listdatatoiuu.clear();

    QString text;
    QList<QString> listfull = data.split(" ");
    for (uint i = 0; i < listfull.size(); i++)
    {
        text = listfull.at(i);
        chinh(text);
        listdatatoiuu.append(text.toLower());
    }
    listdatatoiuu.removeDuplicates();

    if (!map.isEmpty())
        map.clear();

    loadMap();
}

bool DataBase::isGhep(const QString &str)
{
    bool ret = false;
    QString text = str;
    if (str.contains('_') && m_listdoi.contains(text.replace('_',' ')))
        ret = true;
    return ret;
}

QByteArray DataBase::getDataBase(const QString &text)
{
    QByteArray ret;
    if (isNumber(text))
    {
        return ret;
    }
    else
        return Data(text);
}

void DataBase::setGiongDataBase(const QString &giong)
{
    pathGiong = giong;
    readMap();
    checkHead();
    loadListghep();
}
void DataBase::checkData(const QString &str)
{
    QString data = str;
//    QList()
//            for(int i = 0; i < data.l)
}

void DataBase::readMap()
{
    QFile f(QString("./conf") + '/' + pathGiong + "/map");
    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream in(&f);
        in.setCodec("UTF-8");
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList l = line.split(" ");
            if (l.size() == 3)
                configmap[l.at(0)] = {l.at(1).toInt(),l.at(2).toInt()};
        }
        f.close();
    }
}

bool DataBase::isNumber(const QString &text)
{
    return false;
}

QByteArray DataBase::Data(const QString &textQS)
{
    QByteArray ret;
    if(map.contains(textQS)){
        ret = map[textQS];
    }
    return ret;
}

void DataBase::readsetting()
{
    QFile f("setting.json");

    if(f.open(QIODevice::ReadOnly))
    {
        QByteArray data = f.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        if(obj["Setting"].toObject().contains("data"))
        {
//            link = obj["Setting"].toObject().value("data").toString();
            file = obj["Setting"].toObject().value("file").toString();
            folder = obj["Setting"].toObject().value("folder").toString();
        }
        f.close();
    }
}
void DataBase::writeSetting()
{
    QFile f("setting.json");
    if(f.open(QIODevice::WriteOnly))
    {
        QJsonObject obj,parse;
        obj["file"] = file;
        obj["folder"] = folder;

        parse["Setting"] = obj;
        QJsonDocument doc(parse);
        QByteArray data = doc.toJson();
        f.write(data);
        f.close();
    }
}
void DataBase::updateFileFolder(const QString& file,const QString& folder)
{
    this->file = file;
    this->folder = folder;
}
void DataBase::AddList(QStringList &list1){}
void DataBase::loadMap()
{
    QDir d("./conf/");
    if(d.exists())
    {
        QFile f2(d.path() +'/'+ pathGiong + "/conf");
        if (f2.open(QIODevice::ReadOnly))
        {
            QStringList list1;
            if(!configmap.isEmpty()){
                list1 = listdatatoiuu;
                AddList(list1);
                for(const auto &i :qAsConst(list1))
                {
                    QByteArray b;
                    if (configmap.contains(i)){
                        int start = configmap[i].first+661995;
                        int end = configmap[i].second;
                        if(f2.seek(start))
                        {
                            char arr[100000];
                            memset(arr,0,100000);
                            f2.read(arr,end);
                            b = QByteArray(arr,end);
                            map.insert(i,b);
                        }
                    }
                }
            }
        }
    }
}

void chinh(QString& textpos)
{
    textpos.remove("《");
    textpos.remove("》");
    textpos.remove("】");
    textpos.remove("【");
    textpos.remove(',');
    textpos.remove('.');
    textpos.remove('!');
    textpos.remove('"');
    textpos.remove('?');
    textpos.remove("…");
    textpos.remove('"');
    textpos.remove(':');
    textpos.remove('(');
    textpos.remove(')');
    textpos.remove('-');
    textpos.remove('+');
    textpos.remove('|');
    textpos.remove('&');
    textpos.remove('%');
    textpos.remove('$');
    textpos.remove('@');
    textpos.remove('=');
    textpos.remove('_');
    textpos.remove('*');
    textpos.remove('^');
    textpos.remove('[');
    textpos.remove(']');
    textpos.remove('{');
    textpos.remove('}');
    textpos.remove('\'');
    textpos.remove("–");
    textpos.remove("—");
    textpos.remove('\t');
    textpos.remove('\n');
    textpos.remove('\r');
    textpos.remove('\f');
    textpos.remove('\\');
    textpos.remove('/');
    textpos.remove("’");
    textpos.remove("‘");
    textpos.remove("~");
    textpos.remove(";");
    textpos.remove(",");
    textpos.remove("?");
    textpos.remove("”");
    textpos.remove("“");
}

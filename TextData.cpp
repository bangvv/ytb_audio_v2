#include "TextData.h"
#include <QFile>
#include <QDir>

bool TextData::hasNumber(const QString &text)
{
    bool ret = false;
    for(auto i: text)
    {
        if(i.isNumber()){
            ret = true;
            break;
        }
    }
    return ret;
}

bool TextData::isNumber(const QString &text)
{
    bool ret = true;
    for(auto i: text)
    {
        if(!i.isNumber()){
            ret = false;
            break;
        }
    }
    return ret;
}

QString TextData::createString(const QString &text)
{
    QString ret = text;
    if (isNumber(ret))
        ret = convertNumberToVietnameseWord(ret.toInt());
    else if (hasNumber(ret)){
        ret = updateNumber(text);
        UpdateText(ret);
    }
    else {}

    return ret;
}

bool TextData::hasUp(const QString &text)
{
    bool ret = false;
    int index = 0;
    for(auto i : text)
    {
        if (index!=0 &&i.isUpper())
        {
            ret = true;
            break;
        }
        index++;
    }
    return ret;
}

QString TextData::createUp(const QString &text)
{
    QString ret = text;
    for(auto i : ret)
    {
        if (i.isUpper())
        {
            QString rp (i);
            ret.replace(rp," "+rp);
            break;
        }
    }
    return ret;
}

TextData::TextData()
{

}

TextData::~TextData()
{

}

QString TextData::convertNumberToVietnameseWord(int number) {
    QString words[11] = {"không", "một", "hai", "ba", "bốn", "năm", "sáu", "bảy", "tám", "chín", "mười"};
    QString result = "";
    if (number == 0) {
        result = words[0];
    } else if (number < 0) {
        result = "âm " + convertNumberToVietnameseWord(abs(number));
    } else if (number <= 10) {
        result = words[number];
    } else if (number < 20) {
        result = "mười " + words[number % 10];
    } else if (number < 100) {
        result = words[number / 10] + " mươi " + words[number % 10];
        if (words[number % 10] == "một") {
            result = words[number / 10] + " mươi mốt";
        }
    } else if (number < 1000) {
        result = words[number / 100] + " trăm " + convertNumberToVietnameseWord(number % 100);
    } else if (number < 1000000) {
        result = convertNumberToVietnameseWord(number / 1000) + " nghìn " + convertNumberToVietnameseWord(number % 1000);
    } else if (number < 1000000000) {
        result = convertNumberToVietnameseWord(number / 1000000) + " triệu " + convertNumberToVietnameseWord(number % 1000000);
    } else {
        result = " ";
    }
    return ' '+result+' ';
}

QString TextData::updateNumber(const QString &text)
{
    QString ret;
    bool x,y;
    x = y = false;
    for(auto i :text)
    {
        if (i.isNumber())
        {
            y = false;
        }
        else
            y = true;
        if(x != y)
        {
            x = y;
            ret+=' ';
        }
        ret+=i;
    }
    return ret;
}

void TextData::UpdateText(QString &data)
{
    QList<QString> list = data.split(" ");
    QList<QPair <QString,QString>> listUpdate;
    QStringList upper;
    for(auto i : list)
    {
        if (hasNumber(i))
            listUpdate.push_back({i, ""});
//        else if (hasUp(i))
//            upper.push_back(i);
    }

    for(int i = 0; i < listUpdate.size(); i++)
    {
        listUpdate[i].second = createString(listUpdate[i].first);
    }

    for(int i = 0; i < listUpdate.size(); i++)
    {
        data.replace(listUpdate[i].first, listUpdate[i].second);
    }
//    for(int i = 0; i < upper.size(); i++)
//    {
//        data.replace(upper[i], createUp(upper[i]));
//    }
}

void TextData::HandlerText(QString &data)
{
    data.replace('\n', " . ");
    data.replace("\r\n", " . ");
    data.replace("\n\r", " . ");
    data.replace(".", ". ");
    data.replace("?", "? ");
    data.replace(".", ". ");
    data.replace("!", "! ");
    data.replace("\"", "\" ");
    data.replace("\'", "\' ");
    data.replace("'", "' ");
    data.replace("《","《 ");
    data.replace("》","》 ");
    data.replace("】","】 ");
    data.replace("【","【 ");
    data.replace(",",", ");
    data.replace(".",". ");
    data.replace("!","! ");
    data.replace("\"","\" ");
    data.replace("?","? ");
    data.replace("…","… ");
    data.replace(":",": ");
    data.replace("(","( ");
    data.replace(")",") ");
    data.replace("-","- ");
    data.replace("+","+ ");
    data.replace("|","| ");
    data.replace("&","& ");
    data.replace("%","% ");
    data.replace("$","$ ");
    data.replace("@","@ ");
    data.replace("=","= ");
    data.replace("_","_ ");
    data.replace("*","* ");
    data.replace("^","^ ");
    data.replace("[","[ ");
    data.replace("]","] ");
    data.replace("{","{ ");
    data.replace("}","} ");
    data.replace("–","– ");
    data.replace("—","— ");
    data.replace("\t","\t ");
    data.replace("\n","\n ");
    data.replace("\r","\r ");
    data.replace("\f","\f ");
    data.replace("\\","\\ ");
    data.replace("/","/ ");
    data.replace("’","’ ");
    data.replace("‘","‘ ");
    data.replace("~","~ ");
    data.replace(";","; ");
    data.replace(",",", ");
    data.replace("?","? ");
    data.replace("”","” ");
    data.replace("“","“ ");
}

void TextData::CreateError(const QString &text)
{
    QDir dir("./Error");
    if (dir.exists())
    {
        QFile f(dir.path() + "/Error.txt");
        if (f.open(QIODevice::ReadWrite ))
        {
            f.write(text.toUtf8());
            f.close();
        }
    }
}

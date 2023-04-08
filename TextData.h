#ifndef TEXTDATA_H
#define TEXTDATA_H
#include <QString>
#include <QPair>
#include <QList>

class TextData
{
    bool hasNumber(const QString& text);
    bool isNumber(const QString& text);
    QString createString(const QString& text);
    bool hasUp(const QString& text);
    QString createUp(const QString& text);
public:
    TextData();
    ~TextData();
    QString convertNumberToVietnameseWord(int number);
    QString updateNumber(const QString& text);
    void UpdateText(QString & data);
    void HandlerText(QString & data);
    void CreateError(const QString& text);

};
#endif // TEXTDATA_H

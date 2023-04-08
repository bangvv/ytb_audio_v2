#ifndef WAV_H
#define WAV_H

#include <QFile>
#include <QString>
#include <QByteArray>

class Wav
{
public:
    Wav();
    ~Wav();

    QByteArray      createWavFile(const QByteArray& data);
    QByteArray      removeHead(const QByteArray& data);
    bool            isReady();
    void            initHeadWav(const QByteArray& data);
    void            appendWav(const QByteArray& data, bool ketthuc);
    void            SetNameFile(const QString &Name);
    QString         GetNameFile();
    void            resetInfor();
    bool            state();
    QByteArray      HandleNam01(QByteArray& byte, const QString& text);
    QByteArray      HandleNu01(QByteArray& byte, const QString& text);
private:
    uint            sum1kbyte(const QByteArray& byte);
    uint            findpossize(const QByteArray& byte);
    QString         m_name;
    QByteArray      m_Head;
    QByteArray      datamax3gb;
    int             m_sizeHead;
    uint64_t        size {0};
    bool            m_final{false};
};

#endif // WAV_H

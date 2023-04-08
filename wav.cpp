#include "wav.h"
#include <QDir>


static char buffd[1024];
Wav::Wav():m_Head(0) {
    memset(buffd,0,1024);
}

Wav::~Wav() {}
void Wav::initHeadWav(const QByteArray& data)
{
    if (!m_Head.isEmpty())
        m_Head.clear();
    int pos = 0;
    for (int i = 3;i < data.size() - 4; i++)
    {
        if (data[i] == 'd' &&
            data[i+1] == 'a' &&
            data[i+2] == 't' &&
            data[i+3] == 'a')
        {
            pos = i+8;
        }
    }
    if (pos != 0){
        m_Head = data.mid(0,pos);
        m_sizeHead = m_Head.size();
    }
}

QByteArray Wav::createWavFile(const QByteArray &data)
{
    QByteArray ret;
    return ret;
}

bool Wav::isReady()
{
    return !m_Head.isEmpty() && !m_name.isEmpty();
}

void Wav::appendWav(const QByteArray &dt, bool ketthuc)
{
    if(!m_name.isEmpty()){
         QFile f(m_name);
         if(f.open(QIODevice::ReadWrite))
         {
             QByteArray data,sizew;
             if(f.size() == 0 && m_Head.isEmpty())
             {
                 initHeadWav(dt);
                 if (!m_Head.isEmpty())
                    f.write(m_Head);
             }
             data = removeHead(dt);
             if(datamax3gb.size() < 3145728 && !ketthuc)
             {
                 datamax3gb += data;
             }
             else
             {
                 datamax3gb += data;
                 size += datamax3gb.size();
                 if(m_sizeHead != 0 &&  f.seek(4))
                 {
                     size+=(m_sizeHead-8);
                     char* ptr =(char*)(&size);
                     for(int i = 0; i < 4; i++){
                         sizew.append(*ptr);
                         ptr++;
                     }
                     f.write(sizew);
                 }
                 if(f.seek(m_sizeHead-4))
                 {
                     size -= (m_sizeHead-8);
                     char* ptr =(char*)(&size);
                     for(int i = 0; i < 4; i++){
                         sizew.append(*ptr);
                         ptr++;
                     }
                     f.write(sizew);
                 }
                 if(f.seek(f.size()))
                 {
                     f.write(datamax3gb);
                 }
                 datamax3gb.clear();
             }
             f.close();
             if (ketthuc){
                m_final = true;
             }
         }
    }
}

QByteArray Wav::removeHead(const QByteArray &data)
{
    return data.mid(m_sizeHead);
}

void Wav::SetNameFile(const QString &Name) {
    QDir p;
    int i = 0;
    bool e = true;
    while(e){
        if(!p.exists(Name + " [" + QString::number(i) + "]" + ".wav"))
        {
            m_name = Name + " [" + QString::number(i) + "]" + ".wav";
            e = false;
        }
        i++;
    }
}

QString Wav::GetNameFile()
{
    return m_name;
}

void Wav::resetInfor()
{
    m_name = "";
    m_Head.clear();
    datamax3gb.clear();
    m_sizeHead=0;
    size = 0;
    m_final = false;
}

bool Wav::state()
{
    return m_final;
}

QByteArray Wav::HandleNam01(QByteArray &byte, const QString& text)
{
    QByteArray ret,head,payload;
    int size = findpossize(byte);
    head = byte.mid(0,size);
    payload = byte.mid(size);
    memset(buffd,0,1024);
    int x = payload.size();
    if (text.mid(0,2) == "kh")
    {
        payload = payload.mid(7000,x-7000-1000);
    }else{
        if (x > 27000 && x < 35000)
            payload = payload.mid(5000,x-5000-1000);
        else if (x < 27000 && x > 20000)
            payload = payload.mid(3000,x-3000-1000);
        else if (x > 16000 && x < 20000)
            payload = payload.mid(2500,x-2500-1000);
    }
    x = payload.size();
    if (x < 15000)
    {
        payload = QByteArray(buffd,1024) + payload + QByteArray(buffd,2048);
//        payload = QByteArray(buffd,1024) + payload + QByteArray(buffd,1024);
    }
    if (x < 16000 && x > 15000)
    {
//        payload = QByteArray(buffd,512) + payload + QByteArray(buffd,512);
        payload = QByteArray(buffd,1024) + payload + QByteArray(buffd,1024);
    }
    if (x > 16000 && x < 19000)
    {
        payload = QByteArray(buffd,512) + payload + QByteArray(buffd,1024);
    }
    ret = head+payload;
    return ret;
}

QByteArray Wav::HandleNu01(QByteArray &byte, const QString &text)
{
    QByteArray ret,head,payload;
    int size = findpossize(byte);
    head = byte.mid(0,size);
    payload = byte.mid(size);
    int x = payload.size();
    if (x > 12000)
        payload = payload.mid(1000,x-1500);
//    else if(x >8000 && x < 12000)
//        payload = QByteArray(buffd,256) + payload + QByteArray(buffd,256);
    else if (x < 6500)
        payload = QByteArray(buffd,256) + payload + QByteArray(buffd,512);

    ret = head+payload;
    return ret;
}

uint Wav::sum1kbyte(const QByteArray &byte)
{
    uint sum = 0;
    short* ptr = (short*)byte.data();
    for(int i = 0; i < byte.size(); i+=2)
    {
        if (* ptr > 0)
            sum+=*ptr;
    }
    return sum;
}

uint Wav::findpossize(const QByteArray &data)
{
    uint pos = 0;
    for (int i = 3;i < data.size() - 4; i++)
    {
        if (data[i] == 'd' &&
            data[i+1] == 'a' &&
            data[i+2] == 't' &&
            data[i+3] == 'a')
        {
            pos = i+8;
        }
    }
    return pos;
}

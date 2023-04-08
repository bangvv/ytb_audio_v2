#ifndef MENU_H
#define MENU_H
#include <QObject>
#include <QString>
class MyMenu : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString menutype READ menutype WRITE setMenutype NOTIFY menutypeChanged)
public:
    MyMenu(QObject *parent = nullptr);
    virtual ~MyMenu();

    Q_INVOKABLE bool isHome();
    Q_INVOKABLE bool isLogin();
    Q_INVOKABLE bool isHelp();
    Q_INVOKABLE bool isIntro();

    QString menutype();
    void setMenutype(QString type);
private:
    static QString stype;
    QString m_menutype{"UNKNOW"};
signals:
    void menutypeChanged();
    void updatetypeChanged();

};

#endif // MENU_H

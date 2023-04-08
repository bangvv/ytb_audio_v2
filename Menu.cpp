#include "Menu.h"

MyMenu::MyMenu(QObject *parent) : QObject(parent) {}
MyMenu::~MyMenu(){}
QString MyMenu::stype = "UNKNOW";
QString MyMenu::menutype()
{
    return m_menutype;
}

void MyMenu::setMenutype(QString type)
{
    m_menutype = type;
    stype = m_menutype;
    emit menutypeChanged();
    emit updatetypeChanged();
}

bool MyMenu::isHome(){
    return ("HOME"==stype?true:false);
}
bool MyMenu::isLogin(){
    return ("LOGIN"==stype?true:false);
}
bool MyMenu::isHelp(){
    return ("HELP"==stype?true:false);
}
bool MyMenu::isIntro(){
    return ("INTRO"==stype?true:false);
}

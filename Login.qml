import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "./" as Mycomponent

Rectangle {
    id:idlogin
    visible: mymenupage.showLogin
    TextField{
        placeholderText: "account"
        selectByMouse : true
        id: textselectfile
        width: 366
        height: 30
        x: 160
        y: 60
            }
    TextField{
        placeholderText: "password"
        selectByMouse : true
        echoMode: TextInput.Password
        id: textselectfolder
        width: 366
        height: 30
        x: 160
        y: 100
    }
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import MyMenu 1.0

Row {
    property bool showHome: true
    property bool showLogin: false
    property bool showHelp: false
    property bool showIntro: false
    MyMenu{
        id:mymenu
        onUpdatetypeChanged:{
            console.log("run ok!")
            showHome = mymenu.isHome()
            showLogin = mymenu.isLogin()
            showHelp = mymenu.isHelp()
            showIntro = mymenu.isIntro()
        }
    }
    anchors.top: parent
    Repeater{
        model: ["Home","Login","Intro","Help"]
        Button {
            text: modelData
            width: 70
            height: 40
            background: Rectangle {
                            color: parent.down ? "#bbbbbb" :
                                    (parent.hovered ? "#d6d6d6" : "#f6f6f6")
                    }
            onClicked: {
                if(text === "Login"){
                    mymenu.menutype = "LOGIN"
                }
                else if(text === "Intro"){
                    mymenu.menutype = "INTRO"
                }
                else if(text === "Help"){
                    mymenu.menutype = "HELP"
                }
                else if(text === "Home"){
                    mymenu.menutype = "HOME"
                }
            }
        }
    }
}


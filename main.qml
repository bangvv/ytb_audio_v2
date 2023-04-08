import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "./" as Mycomponent

Window {
    width: 550
    height: 700
    visible: true
    title: qsTr("Text To Speech")
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    Mycomponent.Menu{
        id: mymenupage
    }

    Mycomponent.Home{
        id: homepage
    }
    Mycomponent.Login{
        id: loginpage
    }

}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "./" as Mycomponent
import Handler 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.1
import QtMultimedia 5.0

Rectangle {
    id:idhome
    visible: mymenupage.showHome
    Handler{
        id: idhandler
        onSochuChanged: {
            idsochu.text = idhandler.sochu.toString()
//            idsokitu.text = idhandler.sokitu.toString()
        }
        onProgressChanged: {
            idprogressBar.value = idhandler.progress
        }
        onVfileChanged: textselectfile.text = idhandler.vfile
        onVfolderChanged: textselectfolder.text = idhandler.vfolder
//        onMediafileChanged: mediaPlayer.source = idhandler.mediafile

    }

    TextField{
        placeholderText: "Nhập vào đây!"
        selectByMouse : true
        id: textselectfile
        width: 343
        height: 30
        x: 160
        y: 60
    }
    TextField{
        placeholderText: "Nhập vào đây!"
        selectByMouse : true
        id: textselectfolder
        width: 343
        height: 30
        x: 160
        y: 100

    }
    FileDialog {
        id: fileDialog
        title: "Open File"
        selectMultiple: false
        nameFilters: ["Text files (*.txt)"]
        function seturl(urlnew){
            if (urlnew !== "")
                fileDialog.folder = "file:///" + urlnew
        }
        onAccepted: {
            idhandler.vfile = fileDialog.fileUrl
            textselectfile.text = idhandler.vfile
        }
    }
    FileDialog {
        id: folderDialog
        title: "Open Folder"
        selectMultiple: false
        selectFolder : true
        function seturl(urlnew){
            if (urlnew !== "")
                folderDialog.folder = "file:///" + urlnew
        }
        onAccepted: {
            idhandler.vfolder = folderDialog.fileUrl
            textselectfolder.text = idhandler.vfolder
        }
    }
    Button{
        x: 27
        y: 60
        width: 113
        height: 30
        text: "Select File"
        background: Rectangle{
            border.color: "#f6f6f6"
            color: parent.down ? "#bbbbbb" :
                                 (parent.hovered ? "#d6d6d6" : "#f6f6f6")
        }
        onClicked: {
            fileDialog.seturl(idhandler.getpath(idhandler.vfile))
            fileDialog.open()

        }
    }
    Button{
        x: 27
        y: 100
        width: 113
        height: 30
        text: "Select Folder"
        background: Rectangle{
            border.color: "#f6f6f6"
            color: parent.down ? "#bbbbbb" :
                                 (parent.hovered ? "#d6d6d6" : "#f6f6f6")
        }
        onClicked: {
            folderDialog.seturl(idhandler.vfolder)
            folderDialog.open()
        }
    }

    TextField {
        id: idsokitu
        x: 92
        y: 275
        width: 186
        height: 30
        readOnly: true
        selectByMouse: true
        text: "0"
    }

    TextField {
        id: idsochu
        x: 92
        y: 199
        width: 186
        height: 30
        readOnly: true
        selectByMouse: true
        text : "0"
    }

    ComboBox {
        id:idgiong
        x: 377
        y: 196
        width: 126
        height: 30
        model: ["Nam 01", "Nữ 01"]
        currentIndex: 0
        onActivated: {
            if (idgiong.currentIndex === 0)
                idhandler.giong = "nam_01"
            else if (idgiong.currentIndex === 1)
                idhandler.giong = "nu_01"
        }
    }


    Text{
        id: idtextsokitu
        x: 25
        y: 282
        text: "Số kí tự:"
    }
    Text{
        id: idtextsochu
        x: 27
        y: 209
        text: "Số chữ:"
    }

    Text {
        id: idtextgiongdoc
        x: 305
        y: 203
        text: "Giọng đọc:"
    }

    Rectangle {
        id: textAreaFrame
        color: "white"
        border.color: "grey"
        border.width: 1
        radius: 1
        x: 27
        y: 307
        width: 414
        height: 172

        ScrollView {
            width: 412
            height: 170
            clip: true
            TextArea  {
                id: myTextArea
                width: 412
                height: contentHeight
                wrapMode: TextInput.Wrap
                selectByMouse : true
                focus: true
                onTextChanged: {
                idsokitu.text = myTextArea.text.length
            }
            }
            contentItem: myTextArea
        }
    }
    ColumnLayout {
        id: idColumnLayout
        x: 441
        y: 350
        scale: 0.75
        property int selectedValue: 1
        RadioButton {
            id:idradioFile
            Text {
                id: idtextradiofile
                x: 47
                y: 8
                text: qsTr("File")
                font.pointSize: 10
            }
            checked: (idColumnLayout.selectedValue === 1?true:false)
            onClicked: idColumnLayout.selectedValue = 1
        }
        RadioButton {
            id:idradioTexbox
            Text {
                id: idtextradiotextbox
                x: 45
                y: 9
                text: qsTr("TextBox")
                font.pointSize: 10
            }
            checked: idColumnLayout.selectedValue === 2
            onClicked: idColumnLayout.selectedValue = 2
        }
    }

    Button {
        x: 218
        y: 559
        width: 113
        height: 30
        text: "Start"
        background: Rectangle {
            color: parent.down ? "#bbbbbb" :
                        (parent.hovered ? "#d6d6d6" : "#f6f6f6")
            border.color: "#f6f6f6"
        }

        onClicked: {
            if (idColumnLayout.selectedValue===1)
                idhandler.getDataStart(myTextArea.text,false)
            else if (idColumnLayout.selectedValue===2)
                idhandler.getDataStart(myTextArea.text,true)
        }

    }
    ProgressBar {
        id: idprogressBar
        x: 67
        y: 523
        width: 414
        height: 26
        from: 0
        to: 100
        value: 1
        Layout.fillHeight: true
        background: Rectangle {
            color: "gray"
            radius: 10
            height: idprogressBar.height
        }
        contentItem: Rectangle {
            color: "green"
            radius: 10
            width: idprogressBar.visualPosition * idprogressBar.width
            height: idprogressBar.height
        }
    }

//    MediaPlayer {
//        id: mediaPlayer
//        source: "file:///C:/Users/Admin/Desktop/Audio Gen/EXE/Data_TachAudio/Out/data [5].wav"
//    }
//    Slider {
//        id: seekSlider
//        x: 20
//        y: 621
//        width: 379
//        height: 30
//        from: 0
//        to: 100
//        value: 0
//        onValueChanged: mediaPlayer.position = seekSlider.value
//    }
//    Button {
//        id: playButton
//        x: 415
//        y: 621
//        width: 88
//        height: 30
//        text: mediaPlayer.playbackState === MediaPlayer.PlayingState ? "Pause" : "Play"
//        onClicked: {
////            if (mediaPlayer.playbackState === MediaPlayer.PlayingState) {
////                mediaPlayer.pause()
////            } else {
////                mediaPlayer.play()
////            }
//                idhandler.playMediaFile(mediaPlayer.source)
//        }
//    }

//    Connections {
//        target: mediaPlayer
//        onPlaybackStateChanged: {
//            playButton.text = mediaPlayer.playbackState === MediaPlayer.PlayingState ? "Pause" : "Play"
//        }
//    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.9;height:900;width:640}
}
##^##*/

import QtQuick.Layouts 1.2
import Qt.labs.folderlistmodel 2.1
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2 as QDiag
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 600
    height: 480
    visible: true
    title: qsTr("Star Wars Battlefront II Classic Profile Editor 1.0")

    MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Open File...")
                onTriggered: openDialog.open();
            }
            MenuItem {
                text: qsTr("Save as ...")
                onTriggered: saveDialog.open();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    QDiag.MessageDialog {
        id: messageDialog
        title: MyEditor.dialogTitle
        text: MyEditor.dialogText
        visible: false
    }

    Connections{
       target: MyEditor
       onShowMessageBox: {
           messageDialog.title = MyEditor.dialogTitle;
           messageDialog.text = MyEditor.dialogText;
           messageDialog.visible = true;
       }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 20

        FileDialog{
            id: openDialog;
            title: "Please choose a profile file";
            nameFilters: ["Profile Files (*.profile)"];
            onAccepted: {
                MyEditor.readFile(openDialog.file)
                openDialog.close()
            }
        }
        QDiag.FileDialog {
            id: saveDialog
            title: "Save profile file"
            nameFilters: ["Profile Files (*.profile)"];
            selectExisting: false
            onAccepted: {
                MyEditor.saveFile(saveDialog.fileUrl)
                saveDialog.close()
            }
        }

        Row {

            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50

            Text {
                topPadding: 5
                text: "Profile Name"
                font.pixelSize: 20
            }

            TextField {
                id: nameInput
                placeholderText: qsTr("Robokitty")
                focus: true
                text: MyEditor.name
            }

            Binding {
                target: MyEditor
                property: "name"
                value: nameInput.text
            }
        }

        Row {

            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50

            Text {
                topPadding: 5
                text: "Career Medals"
                font.pixelSize: 20
            }

            Button {
                text: qsTr("Reset")
                onClicked: {
                    MyEditor.setGunslinger(0)
                    MyEditor.setFrenzy(0)
                    MyEditor.setDemolition(0)
                    MyEditor.setTechnician(0)
                    MyEditor.setMarksman(0)
                    MyEditor.setRegulator(0)
                    MyEditor.setEndurance(0)
                    MyEditor.setGuardian(0)
                    MyEditor.setHero(0)
                }
            }
        }

        Row {

            spacing: 20

            Column{

                spacing: 37
                width: 40

                Text {
                    topPadding: 14
                    text: qsTr("Gunslinger: ")
                }

                Text {
                    text: qsTr("Demolition: ")
                }

                Text {
                    text: qsTr("Regulator: ")
                }

            }

            Column{

                spacing: 10

                TextField {
                    id: gunslingerInput
                    width: 100
                    placeholderText: qsTr("Gunslinger")
                    focus: true
                    text: MyEditor.gunslinger
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "gunslinger"
                    value: gunslingerInput.text
                }

                TextField {
                    id: demolitionInput
                    width: 100
                    placeholderText: qsTr("Demolition")
                    focus: true
                    text: MyEditor.demolition
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "demolition"
                    value: demolitionInput.text
                }

                TextField {
                    id: regulatorInput
                    width: 100
                    placeholderText: qsTr("Regulator")
                    focus: true
                    text: MyEditor.regulator
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "regulator"
                    value: regulatorInput.text
                }

            }

            Column{

                spacing: 37
                width: 40

                Text {
                    topPadding: 14
                    text: qsTr("Guardian: ")
                }

                Text {
                    text: qsTr("Frenzy: ")
                }

                Text {
                    text: qsTr("Technician: ")
                }

            }

            Column{

                spacing: 10

                TextField {
                    id: guardianInput
                    width: 100
                    placeholderText: qsTr("Guardian")
                    focus: true
                    text: MyEditor.guardian
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "guardian"
                    value: guardianInput.text
                }

                TextField {
                    id: frenzyInput
                    width: 100
                    placeholderText: qsTr("Frenzy")
                    focus: true
                    text: MyEditor.frenzy
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "frenzy"
                    value: frenzyInput.text
                }

                TextField {
                    id: technicianInput
                    width: 100
                    placeholderText: qsTr("Technician")
                    focus: true
                    text: MyEditor.technician
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "technician"
                    value: technicianInput.text
                }

            }

            Column{

                spacing: 37
                width: 40

                Text {
                    topPadding: 14
                    text: qsTr("Marksman: ")
                }

                Text {
                    text: qsTr("Endurance: ")
                }

                Text {
                    text: qsTr("War Hero: ")
                }

            }

            Column{

                spacing: 10

                TextField {
                    id: marksmanInput
                    width: 100
                    placeholderText: qsTr("Marksman")
                    focus: true
                    text: MyEditor.marksman
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "marksman"
                    value: marksmanInput.text
                }

                TextField {
                    id: enduranceInput
                    width: 100
                    placeholderText: qsTr("Endurance")
                    focus: true
                    text: MyEditor.endurance
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "endurance"
                    value: enduranceInput.text
                }

                TextField {
                    id: heroInput
                    width: 100
                    placeholderText: qsTr("War Hero")
                    focus: true
                    text: MyEditor.hero
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "hero"
                    value: heroInput.text
                }
            }

        }

        Row {

            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50

            Text {
                topPadding: 5
                text: "Career Stats"
                font.pixelSize: 20
            }

            Button {
                text: qsTr("Reset")
                onClicked: {
                    MyEditor.setPoints(0)
                    MyEditor.setKills(0)
                    MyEditor.setDeaths(0)
                }
            }
        }

        Row {

            spacing: 20

            Column{

                spacing: 37
                width: 40

                Text {
                    topPadding: 14
                    text: qsTr("Points: ")
                }
            }

            Column{

                spacing: 10

                TextField {
                    id: pointsInput
                    width: 100
                    placeholderText: qsTr("Points")
                    focus: true
                    text: MyEditor.points
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "points"
                    value: pointsInput.text
                }

            }

            Column{

                spacing: 37
                width: 40

                Text {
                    topPadding: 14
                    text: qsTr("Deaths: ")
                }

            }

            Column{

                spacing: 10

                TextField {
                    id: deathsInput
                    width: 100
                    placeholderText: qsTr("Deaths")
                    focus: true
                    text: MyEditor.deaths
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "deaths"
                    value: deathsInput.text
                }

            }

            Column{

                spacing: 37
                width: 40

                Text {
                    topPadding: 14
                    text: qsTr("Kills: ")
                }

            }

            Column{

                spacing: 10

                TextField {
                    id: killsInput
                    width: 100
                    placeholderText: qsTr("Kills")
                    focus: true
                    text: MyEditor.kills
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator {
                        bottom: 0
                        top: 100000000
                    }
                }

                Binding {
                    target: MyEditor
                    property: "kills"
                    value: killsInput.text
                }
            }

        }


        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50

            Button {
                text: qsTr("Open")
                onClicked: {
                    openDialog.open();
                }
            }


            Button {
                text: qsTr("Save")
                onClicked: {
                    MyEditor.saveFile("");
                }
            }
        }
    }

}


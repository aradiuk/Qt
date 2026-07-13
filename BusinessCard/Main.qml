import QtQuick

Window {
    id: root
    width: height * 1.586
    height: 300
    minimumHeight: height
    minimumWidth: width
    maximumHeight: height
    maximumWidth: width
    color: "white"

    visible: true
    title: qsTr("Business Card")

    component ContactInfo: QtObject {

        // This is a ContactInfo object which provides the properties to fill in.
        // You can create as many instances of this as you like with different property values.

        // show these properties all the time:
        property string name
        property url photo

        // Basic Info properties:
        property string occupation
        property string company

        // Detailed Info properties:
        property string address
        property string country
        property string phone
        property string email
        property url webSite
    }
    ContactInfo {
        id: myContactInfo
        name: "First Last"
        photo: Qt.resolvedUrl("IDPhoto.png")
        occupation: "QML Enthusiast"
        company: "Indie Soft"
        address: "Candy Cane Lane"
        country: "North Pole"
        phone: "+01 2345 567 890"
        email: "email@server.com"
        webSite: Qt.url("https://www.qt.io")
    }

    component BasicInfo : Item {
        Column {
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.margins: 5
            spacing: 5
            Text {
                font.pointSize: 25
                font.bold: true
                text: myContactInfo.name
            }
            Text {
                font.pointSize: 15
                text: myContactInfo.occupation
            }
            Text {

                font.pointSize: 15
                text: myContactInfo.company
            }
        }
    }

    component DetailedInfo : Item {
        Column {
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.margins: 5
            spacing: 5
            Text {
                font.pointSize: 25
                font.bold: true
                text: myContactInfo.name
            }
            Text {
                font.pointSize: 15
                text: myContactInfo.address
            }
            Text {
                font.pointSize: 15
                text: myContactInfo.country
            }
            Text {
                font.pointSize: 10
                text: myContactInfo.phone
            }
            Text {
                font.pointSize: 10
                text: myContactInfo.email
            }
            Text {
                font.pointSize: 10
                text: myContactInfo.webSite
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        border.width: 1
        radius: 10

        Rectangle {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 5
            anchors.topMargin: 5
            border.width: 1
            radius: 10
            width: root.height * 0.4
            height: root.height * 0.4
            Image {
                anchors.fill: parent
                anchors.margins: 2
                source: myContactInfo.photo
            }
        }
        BasicInfo {
            visible: detailsButton.isShowDetails ? false : true
        }
        DetailedInfo {
            visible: detailsButton.isShowDetails ? true : false
        }
        Rectangle {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 5
            border.width: 5
            radius: 10
            width: 100
            height: 30
            color: "black"
            Rectangle {
                property bool isShowDetails: false

                id: detailsButton
                anchors.fill: parent
                anchors.margins: 1
                radius: 10
                color: isShowDetails ? "white" : "black"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 15
                    color: detailsButton.isShowDetails ? "black" : "white"
                    text: "Details"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: detailsButton.isShowDetails = !detailsButton.isShowDetails
                }
            }
        }
    }


    /* Your solution should contain these key features:

        - A Text element for each of the ContactInfo properties.
        - The name and photo image should be shown all the time.
        - These should be grouped into two categories "Basic Info" and "Details".
        - Create a button using a MouseArea or TapHandler that can be used to
          toggle between showing the two categories of information.
        - Use a larger font size for the name
    */
}


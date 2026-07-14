pragma ComponentBehavior: Bound
// for permitting access to window.themeColor
// from inside any component declarations in this file

import QtQuick
import QtQuick.Shapes

Window {
    id: window

    /* Your solution should contain these key features:

    - Add a Window with dimensions which resemble the kind of
      remote control shape you want

    - Using components from the Qt Quick module such as Text,
      Image, Rectangle and any other components you want to use
      in your design, construct your shape, colors and layout of
      the elements you need.

    - You should include a number of Buttons providing features
      such as Volume +/-, Mute, Channel +/-, Power on/off, and
      perhaps even some cursor arrows.

    - Add image resources to your project and use them in your
      design and try to show how the image URL might be changed
      using bindings inside a string template expression.

    - Add a font to your project and use a FontLoader to be able
      to use the font in your Text components.

    - Create re-usable items using inline components adding any
      "required" properties where necessary

    - Using bindings and signal handlers to connect your UI
      elements to the provided tvControl object (below) so that
      interacting with your Buttons for example, could change
      the visible, enabled, or color of some of the other
      elements based on the changed state of the tvControl
      object’s properties.

    */

    // Here we have chosen a reasonable shape for your
    // remote control, but feel free to design your own.
    width: 240
    height: 740
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint

    MouseArea {
        anchors.fill: parent
        onPressedChanged: function() {
            if(pressed) window.startSystemMove()
        }
    }

    // the window provides a themeColor property which you
    // may use wherever you need to refer to the same color
    property color themeColor: "silver"

    /* Here are a few components you can use to get you going */

    component BorderGradient: Rectangle {
        id: borderGradientRectangle
        property color color2: borderGradientRectangle.color.darker()
        property int rad: 0
        color: window.themeColor
        radius: rad
        gradient: Gradient {
            GradientStop {
                position: 0
                color: borderGradientRectangle.color
            }
            GradientStop {
                position: 1
                color: borderGradientRectangle.color2
            }
        }
    }

    component DoubleBorderGradient: BorderGradient {
        id: doubleBorderGradient

        // DoubleBorderGradient:
        // A BorderGradient with another one nested inside
        // with a specified innerMargin

        property int innerMargin: 2

        BorderGradient {
            // inner gradient
            anchors {
                fill: parent
                margins: doubleBorderGradient.innerMargin
            }

            radius: doubleBorderGradient.radius - doubleBorderGradient.innerMargin

            // swap the colors around
            color: doubleBorderGradient.color2
            color2: doubleBorderGradient.color
        }
    }

    component Button: DoubleBorderGradient {
        id: button

        // Button:
        // A clickable DoubleBorderGradient with a useful
        // clicked signal and a pressed property alias

        readonly property alias pressed: tapHandler.pressed
        signal clicked(int x, int y)

        implicitWidth: 100
        implicitHeight: 40

        radius: Math.min(width, height) / 2

        color: tapHandler.pressed ? window.themeColor : window.themeColor.darker()
        color2: tapHandler.pressed ? window.themeColor.darker() : window.themeColor

        TapHandler {
            id: tapHandler
            gesturePolicy: TapHandler.WithinBounds
            onTapped: function(point) {
                button.clicked(point.position.x, point.position.y)
            }
        }
    }

    component CircleButton: Button {
        id: circleButton
        width: 200
        height: width // a circle

        // The CircleButton uses Item's containmentMask
        // property to return the boolean result of a
        // simplified test to check if the point is inside
        // the circle or not.
        containmentMask: QtObject {
            function contains(clickPoint: point) : bool {
                return (Math.pow(clickPoint.x - circleButton.radius, 2) +
                        Math.pow(clickPoint.y - circleButton.radius, 2))
                        < Math.pow(circleButton.radius, 2)
            }
        }
    }

    QtObject {
        id: tvControl

        // The tvControl object is provided for you to use as a
        // mock back-end providing a number of typical properties
        // and features you might find on a remote control.
        // There are even 5 channels with sample channelNames.

        property int channelNumber: 0
        readonly property string channelName: channelNames[channelNumber]

        // TV Features
        property bool closedCaptionsEnabled: true
        property bool hdrEnabled: true
        property bool castConnected: true
        property bool listening: false
        property bool muted: false
        property real volume: 0.75
        readonly property bool soundOn: !muted && volume > 0

        function incrementVolume() {
            volume = Math.min(1, volume + 0.1)
        }

        function decrementVolume() {
            volume = Math.max(0, volume - 0.1)
        }

        function incrementChannel() {
            channelNumber = Math.min(channelNames.length - 1, channelNumber + 1)
        }

        function decrementChannel() {
            channelNumber = Math.max(0, channelNumber - 1)
        }

        property list<string> channelNames: [
            "News Station",
            "Comedy Cable",
            "Eats and Beats",
            "Weather",
            "Cartoons",
            "Reality TV"
        ]
    }

    // Here we provide a suggested remote control background
    DoubleBorderGradient {
        id: remoteControlBackground
        color: window.themeColor
        anchors.fill: parent
        innerMargin: 8
        radius: 40
    }

    // As a demonstration of one of the Button types,
    // we add a power button.
    CircleButton {
        id: powerButton

        anchors {
            top: parent.top
            right: parent.right
            topMargin: 20
            rightMargin: 20
        }
        width: 40
        height: 40
        color: "darkred"

        Image {
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: "images/power.svg"
            scale: 0.5
        }

        onClicked: window.close()
    }

    component VerticalButton : DoubleBorderGradient {
        property alias topImage: top.source
        property alias bottomImage: bottom.source
        signal topClicked
        signal bottomClicked
        id: verticalButton
        width: 50
        height: 180
        radius: width / 2
        color: tapHandler1.pressed || tapHandler2.pressed ? window.themeColor : window.themeColor.darker()
        color2: tapHandler1.pressed || tapHandler2.pressed ? window.themeColor.darker() : window.themeColor
        Image {
            id: top
            anchors {
                top: parent.top
                topMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            fillMode: Image.PreserveAspectFit
            width: verticalButton.width * 0.75
            TapHandler {
                id: tapHandler1
                onTapped: verticalButton.topClicked()
            }
        }
        Image {
            id: bottom
            anchors {
                bottom: parent.bottom
                bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            fillMode: Image.PreserveAspectFit
            width: verticalButton.width * 0.75
            TapHandler {
                id: tapHandler2
                onTapped: verticalButton.bottomClicked()
            }
        }
    }
    FontLoader {
        id: channelIdFont
        source: "fonts/Silkscreen/Silkscreen-Bold.ttf"
    }
    FontLoader {
        id: channelNameFont
        source: "fonts/Silkscreen/Silkscreen-Regular.ttf"
    }
    DoubleBorderGradient {
        id: display
        anchors {
            top: powerButton.bottom
            left: parent.left
            right: parent.right
            margins: 20
        }
        width: parent.width * 0.85
        height: 100
        radius: 10
        color: "yellowgreen"
        innerMargin: 1
        Text {
            id: channelId
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            font.family: channelIdFont.font.family
            font.pixelSize: 20
            text: "CHANNEL 0" + tvControl.channelNumber
        }
        Text {
            id: channelname
            anchors {
                top: channelId.bottom
                horizontalCenter: parent.horizontalCenter
            }
            font.family: channelNameFont.font.family
            font.pixelSize: 15
            text: tvControl.channelName
        }
        Row {
            spacing: -20
            anchors.bottom: parent.bottom
            Image {
                opacity: tvControl.closedCaptionsEnabled ? true: false
                source: "images/closed_caption.svg"
                scale: 0.6
            }
            Image {
                opacity: tvControl.hdrEnabled ? true: false
                source: "images/hdr_on.svg"
                scale: 0.6
            }
            Image {
                opacity: tvControl.castConnected ? true: false
                source: "images/cast_connected.svg"
                scale: 0.6
            }
            Image {
                opacity: tvControl.listening ? true: false
                source: "images/mic.svg"
                scale: 0.6
            }
        }
        Rectangle {
            id: volumeBar
            anchors {
                right: parent.right
                bottom: parent.bottom
                rightMargin: 10
                bottomMargin: 10
            }
            border.width: 2
            border.color: "black"
            height: display.height * 0.8
            width: 10
            color: "transparent"
            Rectangle {
                anchors.bottom: parent.bottom
                color: "black"
                width: parent.width
                height: parent.height * tvControl.volume
            }
        }
        Image {
            anchors {
                right: volumeBar.left
                rightMargin: -10
                bottom: parent.bottom
            }
            source: tvControl.volume == 0 || tvControl.muted ? "images/speaker_muted.svg" : "images/speaker.svg"
            scale: 0.6
        }
    }
    Row {
        anchors {
            top: display.bottom
            topMargin: 20
            left: remoteControlBackground.left
            leftMargin: 20
        }
        spacing: 5
        Button {
            width: 45
            Image {
                anchors.centerIn: parent
                source: "images/closed_caption_white.svg";
                scale: 0.6
            }
            onClicked: tvControl.closedCaptionsEnabled = !tvControl.closedCaptionsEnabled
        }
        Button {
            width: 45
            Image {
                anchors.centerIn: parent
                source: "images/hdr_on_white.svg";
                scale: 0.6
            }
            onClicked: tvControl.hdrEnabled = !tvControl.hdrEnabled
        }
        Button {
            width: 45
            Image {
                anchors.centerIn: parent
                source: "images/cast_white.svg";
                scale: 0.6
            }
            onClicked: tvControl.castConnected = !tvControl.castConnected
        }
        Button {
            width: 45
            Image {
                anchors.centerIn: parent
                source: "images/speaker_muted_white.svg";
                scale: 0.6
            }
            onClicked: tvControl.muted = !tvControl.muted
        }
    }
    Item {
        id: centralButton
        anchors.centerIn: parent
        width: 200
        height: 200
        Item {
            rotation: 45
            anchors.fill: parent
            Item {
                width: 100
                height: 100
                anchors {
                    left: parent.left
                    top: parent.top
                }
                clip: true
                CircleButton {
                    rotation: -45
                    Image {
                        source: "images/settings.svg"
                        clip: true
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            top: parent.top
                        }
                        scale: 0.7
                    }
                }
            }
            Item {
                width: 100
                height: 100
                rotation: 180
                anchors {
                    right: parent.right
                    bottom: parent.bottom
                }
                clip: true
                CircleButton {
                    rotation: 135
                    Image {
                        source: "images/play_pause.svg"
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            bottom: parent.bottom
                        }
                        scale: 0.7
                        TapHandler {
                            id: tapHandler2
                        }
                    }
                }
            }
            Item {
                width: 100
                height: 100
                rotation: -90
                anchors {
                    left: parent.left
                    bottom: parent.bottom
                }
                clip: true
                CircleButton {
                    rotation: 45
                    Image {
                        source: "images/fast_rewind.svg"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                        }
                        scale: 0.7
                        fillMode: Image.PreserveAspectFit
                        TapHandler {
                            id: tapHandler3
                        }
                    }
                }
            }
            Item {
                width: 100
                height: 100
                anchors {
                    right: parent.right
                    top: parent.top
                }
                rotation: 90
                clip: true
                CircleButton {
                    rotation: 225
                    Image {
                        source: "images/fast_forward.svg"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                        }
                        scale: 0.7
                        fillMode: Image.PreserveAspectFit
                        TapHandler {
                            id: tapHandler4
                        }
                    }
                }
            }
            DoubleBorderGradient {
                anchors.centerIn: parent
                color: color2.darker()
                color2: window.themeColor
                width: 1
                height: parent.height - innerMargin * 2
                rotation: 90
            }
            DoubleBorderGradient {
                anchors.centerIn: parent
                color: color2.darker()
                color2: window.themeColor
                width: 1
                height: parent.height - innerMargin * 2
            }
        }
        CircleButton {
            anchors.centerIn: parent
            width: 100
            height: 100
            Image {
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                source: "images/mic_white.svg"
            }
            onClicked: tvControl.listening = !tvControl.listening
        }
    }
    Button {
        anchors {
            top: centralButton.bottom
            topMargin: 15
            horizontalCenter: centralButton.horizontalCenter
        }
        width: 40
        Text {
            anchors.centerIn: parent
            color: "white"
            text: "Color"
        }

        onClicked: window.themeColor = Qt.rgba(Math.random(), Math.random(), Math.random())
    }

    VerticalButton {
        anchors {
            left: parent.left
            leftMargin: 40
            bottomMargin: 50
            bottom: parent.bottom
        }
        topImage: "images/plus.svg"
        bottomImage: "images/minus.svg"
        onTopClicked: tvControl.incrementChannel()
        onBottomClicked: tvControl.decrementChannel()
    }
    VerticalButton {
        anchors {
            right: parent.right
            rightMargin: 40
            bottomMargin: 50
            bottom: parent.bottom

        }
        topImage: "images/volume_up.svg"
        bottomImage: "images/volume_down.svg"
        onTopClicked: tvControl.incrementVolume()
        onBottomClicked: tvControl.decrementVolume()
    }
}
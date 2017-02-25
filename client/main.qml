import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Rectangle {
    width : 500
    height : 300
    color: "black"

    ColumnLayout{
        spacing: 2

        Button {
            width: 100
            height: 50
            text: "CH1"
            onPressedChanged: {
                if (pressed)
                    console.log("CH1 set close = ", rmtc.doSetChannel(0, true))
                else
                    console.log("CH1 set open = ", rmtc.doSetChannel(0, false))
            }
        }

        Button {
            width: 100
            height: 50
            text: "CH2"
            onPressedChanged: {
                if (pressed)
                    console.log("CH2 set close = ", rmtc.doSetChannel(1, true))
                else
                    console.log("CH2 set open = ", rmtc.doSetChannel(1, false))
            }
        }

        Button {
            width: 100
            height: 50
            text: "CH3"
            onPressedChanged: {
                if (pressed)
                    console.log("CH3 set close = ", rmtc.doSetChannel(2, true))
                else
                    console.log("CH3 set open = ", rmtc.doSetChannel(2, false))
            }
        }

        Button {
            width: 100
            height: 50
            text: "CH4"
            onPressedChanged: {
                if (pressed)
                    console.log("CH4 set close = ", rmtc.doSetChannel(3, true))
                else
                    console.log("CH4 set open = ", rmtc.doSetChannel(3, false))
            }
        }
    }
}

/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-Studio-CLA-applies
 *
 * MuseScore Studio
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore Limited
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
import QtQuick 2.15

import Muse.Ui 1.0
import Muse.UiComponents 1.0
import MuseScore.Palette 1.0

StyledDialogView {
    id: root

    title: qsTrc("palette", "Palette properties")

    contentWidth: 280
    contentHeight: contentColumn.implicitHeight
    margins: 12

    property var properties

    PalettePropertiesModel {
        id: propertiesModel
    }

    Component.onCompleted: {
        propertiesModel.load(properties)
    }

    NavigationPanel {
        id: navPanel
        name: "PalettePropertiesDialog"
        section: root.navigationSection
        enabled: root.enabled && root.visible
        order: 1
        direction: NavigationPanel.Horizontal
    }

    onNavigationActivateRequested: {
        nameField.navigation.requestActive()
    }

    Column {
        id: contentColumn
        anchors.fill: parent
        spacing: 12

        StyledTextLabel {
            text: qsTrc("palette", "Name")
            font: ui.theme.bodyBoldFont
        }

        TextInputField {
            id: nameField
            currentText: propertiesModel.name

            onTextChanged: function(newTextValue) {
                propertiesModel.name = newTextValue
            }

            navigation.panel: navPanel
            navigation.order: 1
        }

        SeparatorLine { anchors.margins: -parent.margins }

        StyledTextLabel {
            text: qsTrc("palette", "Cell size")
            font: ui.theme.bodyBoldFont
        }

        Grid {
            id: grid
            width: parent.width

            columns: 2
            spacing: 12

            Repeater {
                id: repeater

                model: [
                    {
                        title: qsTrc("palette", "Width"),
                        value: propertiesModel.cellWidth,
                        incrementStep: 1,
                        minValue: 1,
                        maxValue: 500
                    },
                    {
                        title: qsTrc("palette", "Height"),
                        value: propertiesModel.cellHeight,
                        incrementStep: 1,
                        minValue: 1,
                        maxValue: 500
                    },
                    {
                        title: qsTrc("palette", "Element offset"),
                        value: propertiesModel.elementOffset,
                        measureUnit: qsTrc("global", "sp"),
                        incrementStep: 0.1,
                        minValue: -10,
                        maxValue: 10
                    },
                    {
                        title: qsTrc("palette", "Scale"),
                        value: propertiesModel.scaleFactor,
                        incrementStep: 0.1,
                        minValue: 0.1,
                        maxValue: 15
                    }
                ]

                function setValue(index, value) {
                    if (index === 0) {
                        propertiesModel.cellWidth = value
                    } else if (index === 1) {
                        propertiesModel.cellHeight = value
                    } else if (index === 2) {
                        propertiesModel.elementOffset = value
                    } else if (index === 3) {
                        propertiesModel.scaleFactor = value
                    }
                }

                Column {
                    width: (grid.width - grid.spacing * (grid.columns - 1)) / grid.columns

                    spacing: 8

                    StyledTextLabel {
                        text: modelData["title"]
                    }

                    IncrementalPropertyControl {
                        currentValue: modelData["value"]
                        measureUnitsSymbol: Boolean(modelData["measureUnit"]) ? modelData["measureUnit"] : ""
                        step: modelData["incrementStep"]
                        minValue: modelData["minValue"]
                        maxValue: modelData["maxValue"]

                        onValueEdited: function(newValue) {
                            repeater.setValue(model.index, newValue)
                        }
                        
                        navigation.panel: navPanel
                        navigation.order: 2 + model.index
                        navigation.accessible.name: modelData["title"] + " " + currentValue
                    }
                }
            }
        }

        CheckBox {
            width: parent.width
            text: qsTrc("palette", "Show grid")

            checked: propertiesModel.showGrid

            onClicked: {
                propertiesModel.showGrid = !checked
            }

            navigation.panel: navPanel
            navigation.order: 2 + repeater.count
        }

        ButtonBox {
            width: parent.width

            buttons: [ ButtonBoxModel.Cancel, ButtonBoxModel.Ok ]

            navigationPanel.section: root.navigationSection
            navigationPanel.order: 2

            onStandardButtonClicked: function(buttonId) {
                if (buttonId === ButtonBoxModel.Cancel) {
                    propertiesModel.reject()
                    root.hide()
                } else if (buttonId === ButtonBoxModel.Ok) {
                    root.hide()
                }
            }
        }
    }
}

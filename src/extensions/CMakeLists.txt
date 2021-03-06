# SPDX-License-Identifier: GPL-3.0-only
# MuseScore-CLA-applies
#
# MuseScore
# Music Composition & Notation
#
# Copyright (C) 2021 MuseScore BVBA and others
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

set(MODULE extensions)

set(MODULE_QRC extensions.qrc)

set(MODULE_QML_IMPORT ${CMAKE_CURRENT_LIST_DIR}/qml )

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/extensionsmodule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/extensionsmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/iextensionsservice.h
    ${CMAKE_CURRENT_LIST_DIR}/iextensionsconfiguration.h
    ${CMAKE_CURRENT_LIST_DIR}/iextensionunpacker.h
    ${CMAKE_CURRENT_LIST_DIR}/extensionstypes.h
    ${CMAKE_CURRENT_LIST_DIR}/extensionserrors.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/extensionsservice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/extensionsservice.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/extensionsconfiguration.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/extensionsconfiguration.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/extensionunpacker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/extensionunpacker.h
    ${CMAKE_CURRENT_LIST_DIR}/view/extensionlistmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/extensionlistmodel.h
    )

set(MODULE_LINK
    qzip
    )

include(${PROJECT_SOURCE_DIR}/build/module.cmake)


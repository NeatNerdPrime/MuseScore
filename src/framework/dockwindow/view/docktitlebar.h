/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
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

#ifndef MUSE_DOCK_DOCKTITLEBAR_H
#define MUSE_DOCK_DOCKTITLEBAR_H

#include "internal/dockbase.h"

#include "thirdparty/KDDockWidgets/src/private/quick/TitleBarQuick_p.h"

#include <QtGlobal>

namespace muse::dock {
class DockTitleBar : public KDDockWidgets::TitleBarQuick
{
    Q_OBJECT

public:
    explicit DockTitleBar(KDDockWidgets::Frame* parent);
    explicit DockTitleBar(KDDockWidgets::FloatingWindow* parent);

    QPoint mapToWindow(QPoint pos) const override;
    Q_INVOKABLE bool doubleClicked(const QPoint& /*pos*/);
};
}

#endif // MUSE_DOCK_DOCKTITLEBAR_H

/*
Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy 
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// application headers
#include "kloudspeakerview.h"

#include "kloudspeakerSettings.h"
#include "kloudspeakerdebug.h"


kloudspeakerView::kloudspeakerView(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    handleSettingsChanged();
}

kloudspeakerView::~kloudspeakerView()
{
}

void kloudspeakerView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = kloudspeakerSettings::colorBackground();
    kloudspeakerSettings::setColorBackground(kloudspeakerSettings::colorForeground());
    kloudspeakerSettings::setColorForeground(color);

    handleSettingsChanged();
}

void kloudspeakerView::handleSettingsChanged()
{
    qCDebug(KLOUDSPEAKER) << "kloudspeakerView::handleSettingsChanged()";
    QPalette palette = m_ui.templateLabel->palette();
    palette.setColor(QPalette::Window, kloudspeakerSettings::colorBackground());
    palette.setColor(QPalette::WindowText, kloudspeakerSettings::colorForeground());
    m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    m_ui.templateLabel->setText(i18n("This project is %1 days old", kloudspeakerSettings::ageInDays()));
}


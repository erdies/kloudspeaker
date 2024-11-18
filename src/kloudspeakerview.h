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

#ifndef KLOUDSPEAKERVIEW_H
#define KLOUDSPEAKERVIEW_H

#include "ui_kloudspeakerview.h"
#include <qcolor.h>
#include "driver.h"


/**
 * This class serves as the main window for kloudspeaker.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class kloudspeakerView : public QWidget {
    Q_OBJECT
    
public:
    /**
     * Default Constructor
     */
    //explicit kloudspeakerView(QWidget *parent);
    explicit kloudspeakerView(QWidget *parent = nullptr);
    /**
     * Default Destructor
     */
    ~kloudspeakerView() override;

public Q_SLOTS:
    void switchColors();
    void handleSettingsChanged();
    // void mypaintEvent();

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::kloudspeakerView m_ui;
    void paintEvent( QPaintEvent * ) override;
    void showEvent(QShowEvent *event) override;  // Neue Zeile
	double Xvalue[150];
	void initXvalue();
    int x_position(double x);
    int YScale(double x,int flag);
    driver* drv1;
};

#endif // KLOUDSPEAKERVIEW_H

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
#include "driver.h"

#include <QPainter>
#include <cmath>

kloudspeakerView::kloudspeakerView(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    handleSettingsChanged();
    update(); // Trigger initial paint
    setAttribute(Qt::WA_StyledBackground, true);
    
    drv1 = new driver(this);
    drv1->Impedanz();
    
}

kloudspeakerView::~kloudspeakerView()
{
    delete drv1;
}

void kloudspeakerView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = kloudspeakerSettings::colorBackground();
    kloudspeakerSettings::setColorBackground(kloudspeakerSettings::colorForeground());
    kloudspeakerSettings::setColorForeground(color);
    initXvalue();
    handleSettingsChanged();
}

void kloudspeakerView::handleSettingsChanged()
{
    //QPalette palette = m_ui.templateLabel->palette();
    //palette.setColor(QPalette::Window, kloudspeakerSettings::colorBackground());
    //palette.setColor(QPalette::WindowText, kloudspeakerSettings::colorForeground());
    //m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    //m_ui.templateLabel->setStyleSheet("background-color: transparent;");
    
    // Trigger a repaint
    update();
}

void kloudspeakerView::initXvalue() // This function maps omega values to window coordinates on the x axis
{
	Xvalue[0] = 125.6637061;
	for (int i=1; i<150; i++)
	{
		Xvalue[i] = Xvalue[i-1] * 1.047128548;
	}
}

int kloudspeakerView::x_position(double x)
{
    double w = width();
    return static_cast<int>(w * 0.144764827 * std::log(x * 0.007957747155));
}

int kloudspeakerView::YScale(double x,int flag)   //Scaling on the currend window size in Y direction
{
	double H;
	H = height();
	if (flag==0)
	{
		return (int)(H/6 - x*H/60);
	}
	if (flag==1)
	{
		return (int)(5*H/6 - x*H/60);
	}
	else
	{
		return (int)(H/6 - x*H/60);
	}
}

void kloudspeakerView::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    
    // Hintergrund zeichnen
    painter.fillRect(rect(), QColor(200, 200, 200));  // Hellgrauer Hintergrund

    // Gelbe Linie zeichnen
    // painter.setPen(QPen(Qt::yellow, 12, Qt::DashDotLine, Qt::RoundCap));
    // painter.drawLine(0, 0, 200, 200);

    // Vertikale Linien zeichnen
    QPen pen(QColor(100, 100, 100));  // Dunklere Farbe für bessere Sichtbarkeit
    pen.setWidth(1);
    painter.setPen(pen);
    
    int i, j;
    for (i = 30; i <= 100; i += 10)
    {
        j = x_position(i * 6.28318);
        painter.drawLine(j, 0, j, height());
    }
    for (i = 200; i <= 1000; i += 100)
    {
        j = x_position(i * 6.28318);
        painter.drawLine(j, 0, j, height());
    }
    for (i = 2000; i <= 10000; i += 1000)
    {
        j = x_position(i * 6.28318);
        painter.drawLine(j, 0, j, height());
    }
    
    // Horizontale Linien zeichnen
    for (i = 1; i <= 30; i++)
    {
        if (i != 5 && i != 10 && i != 15 && i != 20 && i != 25 && i != 30)
        {
            painter.drawLine(0, i * height() / 30, width(), i * height() / 30);
        }
    }

    // Text zeichnen
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    //painter.drawText(rect(), Qt::AlignCenter, "kloudspeakerView is working!");
    painter.drawText(x_position(90*6.28),50*height()/63,"100 Hz");
    painter.drawText(x_position(900*6.28),50*height()/63,"1 kHz");	
    painter.drawText(x_position(9000*6.28),50*height()/63,"10 kHz");	
    painter.drawText(5,100*height()/625,  "0 dB");	
    painter.drawText(1,200*height()/610,"-10 dB");	
    painter.drawText(1,300*height()/605,"-20 dB");	
    painter.drawText(1,400*height()/605,"10 Ohm");	
    painter.drawText(1,500*height()/605,"0 Ohm");	
    
    // Write Impedance
    pen.setWidth(1);
    painter.setPen( pen );
    
    double impedance[200];
    int intJ = 0;
    for (int intI = 0; intI < 300; intI = intI + 2 ) {
        impedance[ intJ ] = sqrt( pow( drv1->ResultImpedanz[ intI ], 2.0 ) + pow( drv1->ResultImpedanz[ intI + 1 ], 2.0 ) );
        intJ++;
    }
    double omega = 125.6637061;
    for (i=1; i<150; i++) {
        //painter.drawLine(x_position( Xvalue[i-1] ), YScale(impedance[i-1], 1), x_position( Xvalue[i] ), YScale(impedance[i], 1));
        painter.drawLine(x_position( omega ), YScale(impedance[i-1], 1), x_position( omega ), YScale(impedance[i], 1));
        omega = omega*1.047128548;
    }
    
    
    
    
    // QWidget::paintEvent aufrufen, um sicherzustellen, dass der Text gerendert wird
    QWidget::paintEvent(event);

}

void kloudspeakerView::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    update();
}

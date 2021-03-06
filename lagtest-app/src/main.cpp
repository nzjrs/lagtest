/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QtGui/QScreen>
#include <QtCore/qmath.h>
#include "qthread.h"

#if QT_VERSION >= 0x050000
    #include <QtGui/QGuiApplication>
#else
    #include <QtGui/QApplication>
#endif

#include "timemodel.h"
#include "ringbuffer.hpp"
#include "serialporthandler.h"
#include "latencymodel.h"

#include "window.h"
#include <QSettings>

#include <QStyleFactory>

#include "lagtest.h"

#include <QDialog>
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationVersion( "0.9.1" );
    app.setStyle( QStyleFactory::create("windowsxp") ); //Do this to prevent bug: https://bugreports.qt-project.org/browse/QTBUG-29720

//#define FLASH
#ifdef FLASH
    Flasher flashIt( QString::fromLocal8Bit(argv[1]), QString::fromLocal8Bit(argv[2]) );
    //Flasher flashIt( "tools/avrdude.exe", "firmware.hex" );
    exit(0);
#else
//    QDialog d;
//    d.setWindowTitle("Dialog one");
//    d.show();
    LagTest lagtest( 300, 1000, 500);
    lagtest.setProperty("ArudinoFirmwareVersion", 3);

#endif
    return app.exec();
}






﻿/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#ifndef DIALOG_H
#define DIALOG_H

#include "wigglywidget.h"
#include <QDialog>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QMenu>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QFont>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QFileDialog>

//! [0]
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    QMenu *pMenu;
    WigglyWidget *wigglyWidget;
    QAction *pAction;
    QMenu *strokeMenu;

    QVBoxLayout *layout;
    QHBoxLayout *hl2;
    QPushButton * pb1;
    QSettings *config;
    QString jpfile;
    QString zhfile;

    QLineEdit *lineEdit;
    bool debug=false;

    void inputUpdate(std::wstring newText);
signals:
    void jOverScreen();

public slots:
    void setDebug(){debug=!debug;/*debug?layout->addWidget(lineEdit):layout->removeWidget(lineEdit);*/ lineEdit->setVisible(debug);}
    void resizedialog(float x, float y);
    void overScreen();
    void mapChooser();
    void stringReloads();
    void BGset();

//protected:
//    void enterEvent(QEvent *);
//    void leaveEvent(QEvent *);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
};
//! [0]

#endif

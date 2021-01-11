/****************************************************************************
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

#include "dialog.h"
#include "wigglywidget.h"
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>

//! [0]
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    WigglyWidget *wigglyWidget = new WigglyWidget;
    QLineEdit *lineEdit = new QLineEdit;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(wigglyWidget);
    //layout->addWidget(lineEdit);

    connect(lineEdit, &QLineEdit::textChanged, this, &Dialog::overScreen);
    connect(lineEdit, &QLineEdit::textChanged, wigglyWidget, &WigglyWidget::setText);
    connect(wigglyWidget, &WigglyWidget::setMainXY, this, &Dialog::resizedialog); //set xy

    //初始位置
    move(QRect(QApplication::desktop()->availableGeometry()).bottomRight().x()/3,QRect(QApplication::desktop()->availableGeometry()).bottomRight().y());
    //setWindowTitle(tr("Wiggly"));
    resize(360, 145); //-280 -335
    lineEdit->setText(tr("Bishojo Game"));


    //透明度
    //setWindowOpacity(0.2);
    //透明
    setAttribute(Qt::WA_TranslucentBackground, true);//需要设置
//    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    //无边框
    setWindowFlag(Qt::FramelessWindowHint);
    //置顶
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    show();


}
//! [0]

void Dialog::resizedialog(int x, int y)
{
    resize(x+20,y);
}
//void Dialog::enterEvent(QEvent *)
//{
//    qDebug()<<"鼠标移入";
//}
//void Dialog::leaveEvent(QEvent *)
//{
//    qDebug()<<"鼠标移出";
//}
void Dialog::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;

        //然后移动窗体即可.
        //this->move(m_windowPoint + relativePos );

        //方法1：
                QDesktopWidget* desktop = QApplication::desktop();
                QRect windowRect(desktop->availableGeometry());
                QRect widgetRect(this->geometry());
        //以下是防止窗口拖出可见范围外
        QPoint point=m_windowPoint + relativePos ;
                //左边
                if (point.x() <= 0)
                {
                    point = QPoint(0,point.y());
                }
                //右边
                int y = windowRect.bottomRight().y() - this->size().height();
                if (point.y() >= y && widgetRect.topLeft().y() >= y)
                {
                    point = QPoint(point.x(),y);
                }
                //上边
                if (point.y() <= 0)
                {
                    point = QPoint(point.x(),0);
                }
                //下边
                int x = windowRect.bottomRight().x() - this->size().width();
                if (point.x() >= x && widgetRect.topLeft().x() >= x)
                {
                    point = QPoint(x,point.y());
                }
                move(point);




                //方法2：
                //可以通过判断QRect windowRect是否包含（contains） QRect widgetRect 再移动
                //这里没有给出代码
    }
}
void Dialog::overScreen()
{

    m_windowPoint = this->frameGeometry().topLeft();
    //方法1：
            QDesktopWidget* desktop = QApplication::desktop();
            QRect windowRect(desktop->availableGeometry());
            QRect widgetRect(this->geometry());

            //qDebug()<<QRect(QApplication::desktop()->availableGeometry()).bottomRight().x()<<QRect(QApplication::desktop()->availableGeometry()).bottomRight().y();

    //以下是防止窗口拖出可见范围外
    QPoint point=m_windowPoint;
            //左边
            if (point.x() <= 0)
            {
                point = QPoint(0,point.y());
            }
            //右边
            int y = windowRect.bottomRight().y() - this->size().height();
            if (point.y() >= y && widgetRect.topLeft().y() >= y)
            {
                point = QPoint(point.x(),y);
            }
            //上边
            if (point.y() <= 0)
            {
                point = QPoint(point.x(),0);
            }
            //下边
            int x = windowRect.bottomRight().x() - this->size().width();
            if (point.x() >= x && widgetRect.topLeft().x() >= x)
            {
                point = QPoint(x,point.y());
            }
            move(point);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}

#pragma once

#include <QWidget>
#include "ui_graphicWindow.h"
#include "lib/qcustomplot.h"

class CGraphicWindow : public QWidget
{
    Q_OBJECT

public:
        CGraphicWindow(QWidget *parent = Q_NULLPTR);
        ~CGraphicWindow();

public:
    void viewGraphic(const QVector<QPair<double, double>>& data, const QColor& color = QColor(Qt::blue), bool calcAxis = false);
    void clear();

private:
    Ui::CGraphicWindow ui;
};

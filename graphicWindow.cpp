#include "graphicWindow.h"

CGraphicWindow::CGraphicWindow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    this->setWindowTitle("График сплайн интерполяции");
}

CGraphicWindow::~CGraphicWindow()
{
}

void CGraphicWindow::viewGraphic(const QVector<QPair<double, double>>& data, const QColor& color, bool calcAxis)
{
    QVector<double> x;
    QVector<double> y;

    for (QPair<double, double> el : data)
    {
        x.push_back(el.first);
        y.push_back(el.second);
    }

    QCPGraph* graphic = ui.m_wGraphicView->addGraph();
    graphic->setData(x, y);
    graphic->setPen(QPen(color));

    ui.m_wGraphicView->xAxis->setLabel("x");
    ui.m_wGraphicView->yAxis->setLabel("y");

    if (calcAxis)
    {
        ui.m_wGraphicView->xAxis->setRange(*std::min_element(x.begin(), x.end()), *std::max_element(x.begin(), x.end()));
        ui.m_wGraphicView->yAxis->setRange(*std::min_element(y.begin(), y.end()), *std::max_element(y.begin(), y.end()));
    }
    
    ui.m_wGraphicView->replot();
}

void CGraphicWindow::clear()
{
    ui.m_wGraphicView->clearGraphs();
}

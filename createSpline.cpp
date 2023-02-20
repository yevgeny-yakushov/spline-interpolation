#include "createSpline.h"
#include "splineInterpolation.h"
#include "graphicWindow.h"

#include "QDebug"

CCreateSpline::CCreateSpline(
	std::function<double(double)> fn,
	double left,
	double right,
	int dotAmount,
	QObject *parent
) :	
	QObject(parent),
	m_fn(fn),
	m_dLeftPoint(left),
	m_dRightPoint(right),
	m_uAmountDot(dotAmount)
{
	m_plotGraphic	= new CGraphicWindow();  m_plotGraphic->show();
	m_spline		= new CSplineInterpolation(m_dRightPoint - m_dLeftPoint + 1);

	calcFunc();
	calcSplines();

	m_plotGraphic->viewGraphic(m_vvdFuncValues									);
	m_plotGraphic->viewGraphic(m_vvdSplineValues,	QColor(Qt::magenta)	,true	);
	m_plotGraphic->viewGraphic(m_vvdErrorValues,	QColor(Qt::red)				);
}

CCreateSpline::~CCreateSpline()
{
	delete m_plotGraphic;	m_plotGraphic	= nullptr;
	delete m_spline;		m_spline		= nullptr;
}

void CCreateSpline::calcFunc()
{
	for (double x = m_dLeftPoint; x <= m_dRightPoint; x++)
	{
		m_vvdFuncValues.push_back({x, m_fn(x)});
	}
}

void CCreateSpline::calcSplines()
{
	if (m_spline->buildSpline(m_vvdFuncValues) == -1)
	{
		qDebug() << "Error build spline";
		return;
	}

	for (double x = m_dLeftPoint; x <= m_dRightPoint; x += (m_dRightPoint - m_dLeftPoint) / m_uAmountDot)
	{
		m_vvdSplineValues.push_back({x, m_spline->interpolate(x)});
		m_vvdErrorValues.push_back({x, qAbs(m_fn(x) - m_vvdSplineValues.last().second)});
		qDebug()
			<< "x = "			<< x
			<< "\tFunc(x) = "	<< m_fn(x)
			<< "\tSpline(x) = "	<< m_vvdSplineValues.last().second
			<< "\tError = "		<< m_vvdErrorValues.last().second;
	}
}
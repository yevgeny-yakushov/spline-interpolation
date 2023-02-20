#pragma once

#include <QObject>
#include <QVector>
#include <QtMath>
#include <functional>

class CGraphicWindow;
class CSplineInterpolation;

class CCreateSpline : public QObject
{
	Q_OBJECT

public:
			CCreateSpline(
				std::function<double(double)> fn,
				double left,
				double right,
				int dotAmount,
				QObject *parent = 0
			);
			~CCreateSpline();

protected:
	void	calcFunc	();
	void	calcSplines	();

private:
	CGraphicWindow*					m_plotGraphic;
	CSplineInterpolation*			m_spline;

	std::function<double(double)>	m_fn;

	QVector<QPair<double, double>>	m_vvdFuncValues;
	QVector<QPair<double, double>>	m_vvdSplineValues;
	QVector<QPair<double, double>>	m_vvdErrorValues;

	double							m_dLeftPoint;
	double							m_dRightPoint;

	int								m_uAmountDot;
};

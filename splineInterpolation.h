#pragma once

#include <QObject>
#include <QVector>
#include <QtMath>

class CSplineInterpolation : public QObject
{
	Q_OBJECT

public:
			CSplineInterpolation(int initN, QObject* parent = 0);
			~CSplineInterpolation();

public:
	int		buildSpline(const QVector<QPair<double, double>>& data);
	double	interpolate(double x);

protected:
	void	sweepMethod(const QVector<QVector<double>>& TDM, const QVector<double>& F);

private:

	QVector<QPair<double, double>>	m_data;
	QVector<QVector<double>>		m_coef;
	QVector<double>					m_b;
	int								m_n;
};

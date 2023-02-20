#include "splineInterpolation.h"

CSplineInterpolation::CSplineInterpolation(int initN, QObject *parent)
	: QObject(parent)
{
	m_n = initN;
	m_b.resize(m_n);
}

CSplineInterpolation::~CSplineInterpolation()
{
}

void CSplineInterpolation::sweepMethod(const QVector<QVector<double>>& matrix, const QVector<double>& F)
{	
	QVector<double> alph(m_n - 1);
	QVector<double> beta(m_n - 1);
	int i;

	alph[0] = -matrix[2][0] / matrix[1][0];
	beta[0] =  F[0]			/ matrix[1][0];

	for (i = 1; i < m_n - 1; i++)
	{
		alph[i] = -matrix[2][i] / (matrix[1][i] + matrix[0][i] * alph[i - 1]);
		beta[i] = (F[i] - matrix[0][i] * beta[i - 1]) / (matrix[1][i] + matrix[0][i] * alph[i - 1]);
	}
	m_b[m_n - 1] = (F[m_n - 1] - matrix[0][m_n - 1] * beta[m_n - 2]) / (matrix[1][m_n - 1] + matrix[0][m_n - 1] * alph[m_n - 2]);

	for (i = m_n - 2; i >= 0; i--)
	{
		m_b[i] = m_b[i + 1] * alph[i] + beta[i];
	}
}

int CSplineInterpolation::buildSpline(const QVector<QPair<double, double>>& data)
{
	m_data = data;

	QVector<double> a(m_n - 1);
	QVector<double> c(m_n - 1);
	QVector<double> d(m_n - 1);
	QVector<double> delta(m_n - 1);
	QVector<double> h(m_n - 1);
	QVector<double> f(m_n);
	QVector<QVector<double>> trigonalMatrix(3);
	double xn;

	if (m_n < 3)
		return -1;

	xn = data[m_n - 1].first - data[0].first;

	for (int i = 0; i < m_n - 1; i++)
	{
		a[i]		= data[i].second;
		h[i]		= data[i + 1].first - data[i].first;
		delta[i]	= (data[i + 1].second - data[i].second) / h[i];

		trigonalMatrix[0].push_back(i > 0 ? h[i] : xn);

		f[i] = i > 0 ? 3 * (h[i] * delta[i - 1] + h[i - 1] * delta[i]) : 0;
	}

	trigonalMatrix[1].push_back(h[0]);
	trigonalMatrix[2].push_back(h[0]);

	for (int i = 1; i < m_n - 1; i++)
	{
		trigonalMatrix[1].push_back(2 * (h[i] + h[i - 1]));
		trigonalMatrix[2].push_back(h[i]);
	}
	
	trigonalMatrix[1].push_back(h[m_n - 2]);
	trigonalMatrix[2].push_back(xn);
	trigonalMatrix[0].push_back(h[m_n - 2]);

	{ // Open local block
		int i = m_n - 1;
		f[0] = ((h[0] + 2 * xn) * h[1] * delta[0] + qPow(h[0], 2) * delta[1]) / xn;
		f[m_n - 1] = (qPow(h[i - 1], 2) * delta[i - 2] + (2 * xn + h[i - 1]) * h[i - 2] * delta[i - 1]) / xn;
	} // Close local block

	sweepMethod(trigonalMatrix, f);

	for (int i = 0; i < m_n - 1; i++)
	{
		d[i] = (m_b[i + 1] + m_b[i] - 2 * delta[i]) / (h[i] * h[i]);
		c[i] = 2 * (delta[i] - m_b[i]) / h[i] - (m_b[i + 1] - delta[i]) / h[i];

		m_coef.push_back({a[i], m_b[i], c[i], d[i]});
	}

	return 1;
}

double CSplineInterpolation::interpolate(double x)
{
	int i = 0;

	for (; m_data[i].first < x; i++);

	i--;
	i = i < 0 ? 0 : i;
	return
		m_coef[i][0] +
		m_coef[i][1] *		(x - m_data[i].first) +
		m_coef[i][2] * qPow((x - m_data[i].first), 2) +
		m_coef[i][3] * qPow((x - m_data[i].first), 3);
}

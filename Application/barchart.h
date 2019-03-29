#ifndef BARCHART_H
#define BARCHART_H

#include <QVector>
#include <QPointF>
#include <QStringList>
#include "glyph.h"

class BarChart : public Glyph
{
public:
    /**
     * @brief BarChart Bar Chart Empty Constructor
     * Default Parameters are Point on {0,0,0}, Size of 0, NEUTRAL transition
     * state,
     * parent origin on {0,0,0}
     */
    BarChart();
    /**
     * @brief BarChart standard constructor
     * @param centroid centroid of where the glyph should be placed.
     * @param size unique size modifier of the glyph
     * @param state transition state, used for animation
     * @param parent parent centroid, used for animation
     */
    BarChart(QPointF centroid, float size, int state, QPointF parent);
    /**
     * @brief initialize sets the values to be presented using the bar chart.
     * @param list list of values to be converted to float
     */
    void initialize(QStringList list);
    /**
     * @brief initialize initialize sets the values to be presented using the
     * bar chart
     * with filtered options.
     * @param list list of values to be converted to float
     * @param filter boolean array depicting values to use.
     */
    void initialize(QStringList list, QVector<bool> filter);
    /**
     * @brief values values depicted by bar chart.
     * @return vector of float holding bar chart values
     */
    QVector<float> values() const;
    /**
     * @brief setValues setter method for vector of float values.
     * @param values
     */
    void setValues(const QVector<float> &values);

private:
    QVector<float> m_values;
};

#endif // BARCHART_H

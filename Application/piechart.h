#ifndef PIECHART_H
#define PIECHART_H

#include <QPointF>
#include <QStringList>
#include <QVector>
#include <cmath>

#include "glyph.h"

class PieSegment
{

public:
    /**
     * @brief PieSegment Pie Segment Empty Constructor
     * Default Parameters are an angle of 1.0f, with a value 0.0f
     *
     */
    PieSegment();
    /**
     * @brief PieSegment standard constructor
     * @param angle angle a pie segment holds in a pie chart.
     * @param value the value represents by the angle.
     */
    PieSegment(float angle, float value);
    /**
     * @brief angle getter method for angle of pie segment
     * @return angle as float representation
     */
    float angle() const;
    /**
     * @brief setAngle setter method for angle
     * @param new angle of pie segment
     */
    void setAngle(float angle);
    /**
     * @brief value getter method for value represented by Pie Segment
     * @return float value
     */
    float value() const;
    /**
     * @brief setValue setter method for value represented by Pie Segment
     * @param value new value of pie segment.
     */
    void setValue(float value);
    /**
     * @brief getIndex getter method for index of place in pie chart. Necessary
     * for filtering
     * @return int representing index in Pie Chart
     */
    int getIndex() const;
    /**
     * @brief setIndex setter method for index of place in pie chart. Necessary
     * for filtering
     * @param value new index
     */
    void setIndex(int value);

private:
    float m_angle = 1.0f;
    float m_value = 0.0f;
    int index = 0;
};

class PieChart : public Glyph
{
public:

    static const int FULL_SLICES = 0;
    static const int EQUAL_SLICES = 1;

    /**
     * @brief PieChart Pie Chart empty constructor
     * Default Parameters are Point on {0,0,0}, Size of 0, NEUTRAL transition
     * state
     */
    PieChart();
    /**
     * @brief PieChart standard constructor
     * @param centroid centroid of where the glyph should be placed.
     * @param size unique size modifier of the glyph
     * @param state transition state, used for animation
     * @param parent parent centroid, used for animation
     */
    PieChart(QPointF centroid, float size, int state, QPointF parent);
    /**
     * @brief initialize initialize values to be represented in pie chart.
     * @param values pie chart values
     */
    void initialize(QStringList values);
    /**
     * @brief maxAngle getter method for maximum angle (2*M_PI)
     * @return maximum angle
     */
    float maxAngle() const;
    /**
     * @brief pieSlices getter method returning list of PieSegments
     * @return vector of pie segments
     */
    QVector<PieSegment> pieSlices() const;
    /**
     * @brief setPieSlices setter method for pie segments
     * @param pieSlices vector of pie segments
     */
    void setPieSlices(const QVector<PieSegment> &pieSlices);
    /**
     * @brief getSliceType getter method for slice type. FULL_SLICES (0)
     * refer to a standard a standard pie chart, EQUAL_SLICES give a pie chart
     * with equal pie segment angles.
     * @return int pertaining to slice type.
     */
    int getSliceType() const;
    /**
     * @brief setSliceType setter method for slice type. FULL_SLICES (0)
     * refer to a standard a standard pie chart, EQUAL_SLICES give a pie chart
     * with equal pie segment angles.
     * @param value new slice type value.
     */
    void setSliceType(int value);
    /**
     * @brief initialize  initialize values of wheel glyph using the mean values
     * @param values list of values to be converted to float
     * @param filters boolean array depicting values to use.
     */
    void initialize(QStringList values, QVector<bool> filters);
private:
    float m_maxAngle = 2*M_PI;
    int sliceType = FULL_SLICES;
    QVector<PieSegment> m_pieSlices;
    /**
     * @brief createEqualSlices method to create equal segment pie chart
     * @param values values to map to pie chart
     */
    void createEqualSlices(QStringList values);
    /**
     * @brief createVariableSlices method to create varying pie slices pie
     * chart.
     * @param values values to map to pie chart
     */
    void createVariableSlices(QStringList values);
    /**
     * @brief createVariableSlices method to create varying pie slices pie
     * chart for value filters.
     * @param values list of values to be converted to pie segments.
     * @param filters boolean array depicting values to use.
     */
    void createVariableSlices(QStringList values, QVector<bool> filters);
};

#endif // PIECHART_H

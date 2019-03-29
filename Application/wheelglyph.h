#ifndef WHEELGLYPH_H
#define WHEELGLYPH_H

#include <QStringList>
#include <QVector>

#include "glyph.h"

class WheelGlyph : public Glyph
{
public:
    /**
     * @brief WheelGlyph Wheel Glyph Empty Constructor
     * Default Parameters are Point on {0,0,0}, Size of 0, NEUTRAL transition
     * state
     */
    WheelGlyph();
    /**
     * @brief WheelGlyph standard constructor
     * @param centroid centroid of where the glyph should be placed.
     * @param size unique size modifier of the glyph
     * @param state transition state, used for animation
     * @param parent parent centroid, used for animation
     */
    WheelGlyph(QPointF centroid, float size, int state , QPointF origin);
    /**
     * @brief initialize sets the values to be presented using the wheel glyph.
     * @param list list of values to be converted to float
     */
    void initialize(QStringList values);
    /**
     * @brief getRads getter method for the wheel glyph values
     * @return vector of floats holding wheel glyph values
     */
    QVector<float> getRads() const;
    /**
     * @brief setRads setter method for the vector of float values
     * @param value new values of wheel glyph
     */
    void setRads(const QVector<float> &value);
    /**
     * @brief initialize initialize values of wheel glyph using the mean values
     * @param values list of values to be converted to float
     * @param means mean per data dimension
     */
    void initialize(QStringList values, QVector<float> means);
    /**
     * @brief initialize initialize values of wheel glyph using the mean values
     * @param values list of values to be converted to float
     * @param filter boolean array depicting values to use.
     */
    void initialize(QStringList values, QVector<bool> filter);
private:
    QVector<float> rads;
};

#endif // WHEELGLYPH_H

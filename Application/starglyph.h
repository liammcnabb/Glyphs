#ifndef STARGLYPH_H
#define STARGLYPH_H

#include "glyph.h"

#include <QStringList>
#include <QVector>

class StarGlyph : public Glyph
{
public:
    /**
     * @brief StarGlyph Star Glyph Empty Constructor
     * Default Parameters are Point on {0,0,0}, Size of 0, NEUTRAL transition
     * state
     */
    StarGlyph();
    /**
     * @brief StarGlyph standard constructor
     * @param centroid centroid of where the glyph should be placed.
     * @param size unique size modifier of the glyph
     * @param state transition state, used for animation
     * @param parent parent centroid, used for animation
     */
    StarGlyph(QPointF centroid, float size, int state , QPointF parent);
    /**
     * @brief initialize sets the values to be presented using the star glyph
     * using max and minimum values.
     * @param values new values of star glyph
     * @param upperBound maximum value
     * @param lowerBound minimum value
     */
    void initialize(QStringList values, float upperBound, float lowerBound);
    /**
     * @brief initialize sets the values to be presented using the star glyph
     * based on mean values
     * @param values new values of star glyph
     * @param means mean per data dimension
     */
    void initialize(QStringList values, QVector<float> means);
    /**
     * @brief points getter method for the star glyph values
     * @return vector of floats holding star glyph values
     */
    QVector<float> points() const;
    /**
     * @brief setPoints setter method for the vector of float values
     * @param points new points of wheel glyph
     */
    void setPoints(const QVector<float> &points);
    /**
     * @brief initialize initialize sets the values to be presented using the
     * star glyph.
     * @param values list of values to be converted to float
     */
    void initialize(QStringList values);
    /**
     * @brief initialize initialize values of wheel glyph using the mean values
     * @param values list of values to be converted to float
     * @param filters boolean array depicting values to use.
     */
    void initialize(QStringList values, QVector<bool> filters);
private:
    QVector<float> m_points;
};

#endif // STARGLYPH_H

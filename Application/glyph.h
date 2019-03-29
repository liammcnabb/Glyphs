#ifndef GLYPH_H
#define GLYPH_H

#include <QPointF>

class Glyph
{
public:
    static constexpr float SIZE_MODIFIER = 0.01;

    static const int NEUTRAL = 0;
    static const int REMOVE = -1;
    static const int ADD = 1;

    /**
     * @brief Glyph main constructor
     * @param centroid Location of glyph placement
     * @param size unique size modifier to be applied to glyph
     * @param state transition state, used for animation
     * @param origin origin centroid, used for animation.
     */
    Glyph( QPointF centroid, float size, int state, QPointF origin );
    /**
     * @brief centroid Getter method for centroid location
     * @return centroid QPointF
     */
    QPointF centroid() const;
    /**
     * @brief setCentroid setter method for centroid of glyph
     * @param centroid new centroid location
     */
    void setCentroid( const QPointF& centroid );
    /**
     * @brief state getter method for transition state used in animation.
     * NEUTRAL state (0) signify non-moving glyphs. ADD state (1) will
     * transition into frame, REMOVE state (-1) will transition out of frame.
     * @return current state.
     */
    int state() const;
    /**
     * @brief setState setter method for transition state. NEUTRAL state (0)
     * signify non-moving glyphs. ADD state (1) will transition into frame,
     * REMOVE state (-1) will transition out of frame.
     * @param state new glyph state
     */
    void setState( int state );
    /**
     * @brief size getter method for unique size modifier, used as a hidden
     * area indicator for this project
     * @return
     */
    float size() const;
    /**
     * @brief setSize setter method for unique size modifier.
     * @param size new size modifier
     */
    void setSize( float size );
    /**
     * @brief parent getter method for origin parent's centroid. If zooming in
     * animation will start her, if zooming out, animation will end here.
     * @return parent's centroid.
     */
    QPointF parent() const;
    /**
     * @brief setParent setter method for parent's centroid
     * @param parent new parent centroid location
     */
    void setParent( const QPointF& parent );

    /**
     * @brief r getter method for RedF value of hidden indicator color
     * @return float RedF
     */
    float r() const;
    /**
     * @brief setR setter method for RedF value of hidden indicator color
     * @param r new RedF value
     */
    void setR( float r );
    /**
     * @brief g getter method for GreenF value of hidden indicator color
     * @return float greenF
     */
    float g() const;
    /**
     * @brief setG setter method for GreenF value of hidden indicator color
     * @param g new GreenF value
     */
    void setG( float g );
    /**
     * @brief b getter method for BlueF value of hidden indicator color
     * @return float BlueF
     */
    float b() const;
    /**
     * @brief setB setter method for BlueF value of hidden indicator color
     * @param b new BlueF value
     */
    void setB( float b );

private:
    QPointF m_centroid;
    QPointF m_parent;
    float m_size = 0.0f;
    int m_state;
    float m_r, m_g, m_b;

};

#endif // GLYPH_H

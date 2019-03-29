#include "gridamalgamate.h"

QVector<TreeNode> GridAmalgamate::amalgamate(QVector<Polygon> nodes,
                                             AABB envelope)
{

    int granularity = 20;
    QVector<AABB> cells;
    QVector<TreeNode> result;
    float cellSize = envelope.length(AABB::XDIM) / granularity;
    float xMin = envelope.minimums[AABB::XDIM];
    float yMin = envelope.minimums[AABB::YDIM];
    for( int i = 0; i < granularity; ++i )
    {
        xMin = envelope.minimums[AABB::XDIM];
        for( int j = 0; j < granularity; ++j )
        {
           cells.append( AABB(xMin, xMin + cellSize, yMin, yMin + cellSize ) );
           xMin += cellSize;
        }
        yMin += cellSize;
    }

    for( int i = 0; i < cells.size(); ++i )
    {
        TreeNode node;
        node.setCentroid(new QPointF( cells[i].minimums[AABB::XDIM] + (
                             cells[i].length( AABB::XDIM ) / 2 ),
                         cells[i].minimums[AABB::YDIM] + (
                             cells[i].length( AABB::YDIM ) / 2 ) ) );
        node.setLevel(1);
        node.setBoundingBox(cells.at(i));
        result.append(node);
    }


    for( int i = 0; i < nodes.size(); ++i )
    {
        int match = 0;
        float distance = std::numeric_limits<float>::max();
        for (int j = 0; j < cells.size(); ++j )
        {
            float temp = fabs( sqrt( pow( nodes[i].centroid()->x() -
                                          result[j].centroid()->x(), 2 ) +
                                     pow( nodes[i].centroid()->y() -
                                          result[j].centroid()->y(), 2 ) ) );
            if( temp < distance )
            {
                match = j;
                distance = temp;
            }
        }
        result[match].values = updateValue( result[match].values,
                                            nodes.at(i).values );
    }

    return result;
}


QStringList GridAmalgamate::updateValue( QStringList values,
                                         QStringList newValues)
{
    if(values.isEmpty())
        return newValues;

    QStringList updated = values;
    for( int i = 0; i < values.size(); ++i )
            updated[i] = QString::number( ( values[i].toFloat()
                                            + newValues[i].toFloat() ) / 2.0f);

    return updated;
}

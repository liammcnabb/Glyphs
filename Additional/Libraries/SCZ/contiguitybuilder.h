#ifndef SCZCONTIGUITYBUILDER_H
#define SCZCONTIGUITYBUILDER_H

#include "SCZ/contiguousarea.h"
#include "SCZ/neighbourchecker.h"
#include "SCZ/segment.h"
//#include "SCZ/objectrenderer.h"

#include <QVector>

class ContiguityBuilder : public Segment
{
public:
    /**
     * @brief SCZContiguityBuilder::SCZContiguityBuilder constructor for
     * contiguity sorting during smooth and continuous zooming procedure
     * @param searchType quality of search to use, shallow or deep (deep search for
     * point-line intersection).
     */
    ContiguityBuilder(int searchType);
    /**
     * @brief SCZContiguityBuilder::sortContiguously
     * @param unsorted list of polygons to sort contiguously
     * @return return a list of contiguous areas
     */
    QVector<ContiguousArea> sortContiguously( QVector<Polygon>
            unsorted );
private:
    /**
     * @brief SCZContiguityBuilder::debugRender send list to be rendered if
     * debug rendering is selected.
     * @param list list to render
     * @param debugMode type of debug render to run
     * @param highlight the index of polygon to highlight
     * @param sleepMul rest multiplier after render
     * @return true if successful
     */
    bool debugRender( QVector<ContiguousArea>* list, int debugMode,
                      int highlight, int sleepMul );
    bool isPartofContiguousArea(Polygon p, ContiguousArea ca);
};

#endif // SCZCONTIGUITYBUILDER_H

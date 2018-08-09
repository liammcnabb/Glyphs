#include "treebuilder.h"

TreeBuilder::TreeBuilder( int searchType,
                                int neighbourType,
                                int recipeType, QString recipeName,
                                int calculationType ) :
    Segment( searchType )
{
    m_mergeInstructions = new QVector<QString>();
    m_loadedRecipe = new QVector<CrfRow>();
    this->neighbourType = neighbourType;

    setRecipeType( recipeType );
    if( recipeType == RECIPE_SAVE )
        m_recipeSaveLocation = recipeName;
    else if ( recipeType == RECIPE_LOAD )
        m_recipeLoadLocation = recipeName;

    setCalculationType( calculationType );

}

double TreeBuilder::selectDefaultValue( Polygon p )
{
    double value = 0;
    if( p.values.size() < 1 )
        value = rand() % COLORGORICAL_MAX;
    else
    {
        if( p.values.size() > 1 )
            value =  p.values.at( 1 ).toDouble();
        else
            qDebug() << "polygon does not contain value, set to 0";
    }


    return value;
}

TreeNode TreeBuilder::createBinaryTree( QVector<Polygon>
        contiguousArea,
        QVector<QString>* instructions,
        QVector<CrfRow>* loadedRecipe )
{
    LinkedList* list = new LinkedList(
        new TreeNode( contiguousArea.at( 0 ) ) );
    list->first()->value = selectDefaultValue( contiguousArea.at(
                               0 ) );

    //Convert to TreeNodes
    for ( int i = 1; i < contiguousArea.size(); i++ )
    {
        list->append( new TreeNode( contiguousArea.at( i ) ) );
        list->last()->value = selectDefaultValue( contiguousArea.at(
                                  i ) );
        list->last()->setLevel(1);
    }

    lowerRange( list, false );

    if( getRecipeType() == RECIPE_LOAD )
        m_loadedRecipe = loadedRecipe;

    if( getRecipeType() == RECIPE_SAVE )
        m_mergeInstructions = instructions;

    if( getCalculationType() == CALC_BY_FREQUENCY )
        calculateValueRange( list );
    buildBinaryTree( list );

    return *list->first();
}

double TreeBuilder::lowerRange( LinkedList* list,
                                   bool returned )
{
    double lower = std::numeric_limits<double>::max();
    for ( int i = 0; i < list->size(); ++i )
        lower = std::min( list->at( i )->getArea(), lower );

    if( !returned )
        setLowerBoundSize( lower );

    return lower;
}


void TreeBuilder::upperRange( LinkedList* list )
{
    double higher = std::numeric_limits<double>::lowest();
    for ( int i = 0; i < list->size(); ++i )
        higher = std::max( list->at( i )->getArea(), m_higherBoundSize );

    setHigherBoundSize( higher );
    return;
}

void TreeBuilder::buildBinaryTree( LinkedList* list )
{
    //    bool success == false;
    qDebug() <<  "2/2: List Size:" << list->size() <<
             QDateTime::currentDateTime().toString();

    if ( list->size() > 1 )
    {
        int neighbour = DEFAULT_INDEX;
        CrfRow indexes;
        TreeNode* parent = new TreeNode();
        if ( getRecipeType() == RECIPE_LOAD )
        {
            indexes = getLoadedRecipe()->first();
            getLoadedRecipe()->pop_front();
            neighbour = indexes.neighbourIndex();
            parent->initNonSharedBoundary( computeParentBoundaries(
                                               list->first(),
                                               list->at( neighbour ),
                                               indexes ) );
        }
        else
        {
            //            while( success == false)
            neighbour = identifyNeighbour( list );
            //            qDebug() << QString::fromStdString(
            //                         list->first()->getBoundingBox().toString() )
            //                     << QString::fromStdString( list->at(
            //                                                    neighbour )->getBoundingBox().toString() );
            parent->initNonSharedBoundary( computeParentBoundaries(
                                               list->first(),
                                               list->at( neighbour ) ) );
        }
        parent->setLeftChild( list->first() );
        parent->setRightChild( list->at( neighbour ) );
        parent->setValues(parent->getRightChild()->getValues());
        parent->setLevel(parent->getLeftChild()->getLevel()+1);
//        applyValue( parent, getCalculationType() );

//        if ( Segment::getDebugMode() )
//        {
//            double lower = lowerRange( list, true );
//            upperRange( list );
//            SCZSegment::renderer()->updateColourManager( higherBoundSize(),
//                    lowerBoundSize(), 6, false );
//        }

        if( getRecipeType() == RECIPE_SAVE )
        {
            QString instruction = QString::number( neighbour ) + ","
                                  + QString::number(
                                      list->first()->getSharedBoundary()->getStartIndex() )
                                  + "," + QString::number(
                                      list->first()->getSharedBoundary()->getEndIndex() )
                                  + "," + QString::number( list->at(
                                              neighbour )->getSharedBoundary()->getStartIndex() )
                                  + "," + QString::number( list->at(
                                              neighbour )->getSharedBoundary()->getEndIndex() );
            m_mergeInstructions->append( instruction );
        }

        updateList( list, parent, neighbour );
        buildBinaryTree( list );
    }
    return;
}

void TreeBuilder::applyValue( TreeNode* node,
                                 int calculationType )
{
    QStringList values = node->getValues();
    for( int i = 0; i < values.size(); ++i )
    {
        switch( calculationType )
        {
        case CALC_BY_ADDITION:
            values[i] = node->getRightChild()->getValues().at(i).toDouble() +
                    node->getLeftChild()->getValues().at(i).toDouble();
            break;
        case CALC_BY_AVERAGE:
            values[i] = calculateValueByAverage( node, i );
            break;
        case CALC_BY_LARGEST:
            values[i] = node->getRightChild()->getValues().at(i).toDouble();
            break;
        case CALC_BY_FREQUENCY:
            values[i] = double(calculateValueByFrequency( node, upperValue, i ));
            break;
        case CALC_BY_AREA_NORMALISED_SUM:
            values[i] = node->getRightChild()->getValues().at(i).toDouble() +
                    node->getLeftChild()->getValues().at(i).toDouble();
            break;
        default:
            values[i] = 0.0;
            break;
        }
    }
}

int TreeBuilder::calculateValueByFrequency( TreeNode* node,
        int upperValue, int fieldIndex )
{
    freq.clear();
    freq.resize( int( upperValue + 1 ) );
    calculateValueByFrequency( node, fieldIndex );

    int highest = 0;
    for ( int i = 0; i < freq.size(); ++i )
        if ( freq.at( highest ) < freq.at( i ) )
            highest = i;

    return highest;

}

void TreeBuilder::calculateValueByFrequency(
    TreeNode* node, int fieldIndex )
{
    if( node->getLeftChild() != nullptr )
        calculateValueByFrequency( node->getLeftChild(), fieldIndex );
    if( node->getRightChild() != nullptr )
        calculateValueByFrequency( node->getRightChild(), fieldIndex );

    if( node->getLeftChild() == nullptr &&
            node->getRightChild() == nullptr )
        freq[node->getValues().at(fieldIndex).toInt()]++;
}

double TreeBuilder::calculateValueByAreaNormalisedSum( TreeNode* node, int fieldIndex )
{
    int vCount = 0;
    double value = 0;
    calculateValueByAverage( &vCount, &value, node, fieldIndex );
    return double( value / node->getArea() );
}

double TreeBuilder::calculateValueByAverage( TreeNode* node, int fieldIndex )
{
    int vCount = 0;
    double value = 0;
    calculateValueByAverage( &vCount, &value, node, fieldIndex );

    return double( value / vCount );

}

void TreeBuilder::calculateValueByAverage( int* vCount,
        double* value, TreeNode* node, int fieldIndex )
{
    if( node->getLeftChild() != nullptr )
        calculateValueByAverage( vCount, value, node->getLeftChild(), fieldIndex );
    if( node->getRightChild() != nullptr )
        calculateValueByAverage( vCount, value, node->getRightChild(), fieldIndex );

    if( node->getLeftChild() == nullptr &&
            node->getRightChild() == nullptr )
    {
        *vCount += 1;
        *value += node->getValues().at(fieldIndex).toDouble();
    }

}

void TreeBuilder::calculateValueRange( LinkedList* list )
{
    //Assume int
    ///TODO add string handling

    upperValue = INT_MIN;
    for( int i = 0; i < list->size(); ++i )
        upperValue = std::max( upperValue, list->at( i )->value );

}

int TreeBuilder::identifyNeighbour( LinkedList* list )
{
    int indexOfClosest = DEFAULT_INDEX;
    switch ( getNeighbourType() )
    {
        case SMALLEST_NEIGHBOUR:
            for ( int i = 1; i < list->size(); ++i )
                if ( NeighbourChecker::isNeighbour( list->first(), i,
                                                    list, Segment::searchType() ) )
                    return i;
            break;
        case CLOSEST_VALUE:

            for ( int i = 1; i < list->size(); ++i )
                if ( NeighbourChecker::isNeighbour( list->first(), i,
                                                    list, Segment::searchType() ) )
                {
                    int distanceI = distance( list->at( i )->value,
                                                     list->first()->value );

                    if ( distanceI == 0 )
                        return i;

                    if ( indexOfClosest == DEFAULT_INDEX )
                        indexOfClosest = i;
                    else if ( distanceI <
                              distance(
                                  list->at( indexOfClosest )->value,
                                  list->first()->value ) )
                        indexOfClosest = i;
                }

            if ( indexOfClosest == DEFAULT_INDEX )
                qDebug() << "No Neighbour Found.";
            return indexOfClosest;
            break;
        case CLOSEST_CENTROID:
            float a, b, c, previousC;

            for ( int i = 1; i < list->size(); ++i )
                if ( NeighbourChecker::isNeighbour( list->first(), i,
                                                    list, Segment::searchType() ) )
                {
                    a = fabs( list->at( i )->centroid()->x() -
                              list->first()->centroid()->x() );
                    b = fabs( list->at( i )->centroid()->y() -
                              list->first()->centroid()->y() );
                    c = sqrt( ( a * a ) + ( b * b ) );

                    if ( indexOfClosest == DEFAULT_INDEX )
                    {
                        indexOfClosest = i;
                        previousC = c;
                    }
                    else if ( c < previousC )
                    {
                        indexOfClosest = i;
                        c = previousC;
                    }
                }

            if ( indexOfClosest == DEFAULT_INDEX )
                qDebug() << "something wrong";

            return indexOfClosest;
            break;
    }

    qDebug() << "No Neighbour Found. " << QString::fromStdString(
                 list->first()->getBoundingBox().toString() ) <<
             "Refer to GIS to look for odd boundary." << "Edge Size =" <<
             list->first()->getNonSharedBoundary()->boundarySize();
    exit( 0 );
    return DEFAULT_INDEX;
}

QVector<QPointF> TreeBuilder::computeParentBoundaries(
    TreeNode* current,
    TreeNode* neighbour )
{
    QVector<QPointF> parentNonSharedVertices;
    splitBoundary( current, neighbour );
    splitBoundary( neighbour, current );

    for( int i = 0;
            i < current->getNonSharedBoundary()->boundarySize();
            ++i )
        parentNonSharedVertices.append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );

    for( int i = 0;
            i < neighbour->getNonSharedBoundary()->boundarySize();
            ++i )
        parentNonSharedVertices.append(
            neighbour->getNonSharedBoundary()->getBoundary().at( i ) );

    return parentNonSharedVertices;
}

QVector<QPointF> TreeBuilder::computeParentBoundaries(
    TreeNode* current,
    TreeNode* neighbour, CrfRow indexes )
{
    QVector<QPointF> parentNonSharedVertices;
    splitBoundary( current, neighbour,
                   indexes.pOneStartIndex(), indexes.pOneEndIndex() );
    splitBoundary( neighbour, current,
                   indexes.pTwoStartIndex(), indexes.pTwoEndIndex() );

    for( int i = 0;
            i < current->getNonSharedBoundary()->boundarySize();
            ++i )
        parentNonSharedVertices.append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );

    for( int i = 0;
            i < neighbour->getNonSharedBoundary()->boundarySize();
            ++i )
        parentNonSharedVertices.append(
            neighbour->getNonSharedBoundary()->getBoundary().at( i ) );

    return parentNonSharedVertices;
}

bool TreeBuilder::splitBoundary( TreeNode* current,
                                    TreeNode* neighbour )
{
    findSharedBoundary( current, neighbour );
    findNonSharedBoundary( current, neighbour );

    return true;
}

bool TreeBuilder::splitBoundary( TreeNode* current,
                                    TreeNode* neighbour,
                                    int indexStart, int indexEnd )
{
    findSharedBoundary( current, neighbour, indexStart, indexEnd );
    findNonSharedBoundary( current, neighbour );

    return true;
}

void TreeBuilder::findSharedBoundary( TreeNode* current,
        TreeNode* neighbour )
{
    int startIndex, endIndex;
    startIndex = endIndex = DEFAULT_INDEX;
    identifyBoundaryRange( &startIndex, &endIndex, current,
                           neighbour );

    current->getSharedBoundary()->setStartIndex( startIndex );
    current->getSharedBoundary()->setEndIndex( endIndex );

    for ( int i = startIndex;
            i < current->getNonSharedBoundary()->getBoundary().size(); ++i )
    {
        current->getSharedBoundary()->getBoundary().append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );

        if ( i == endIndex )
            return;
    }

    for ( int i = 0; i <= endIndex; ++i )
    {
        current->getSharedBoundary()->getBoundary().append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );
    }

    return;
}

void TreeBuilder::findSharedBoundary( TreeNode* current,
        TreeNode* neighbour,
        int indexStart, int indexEnd )
{
    int startIndex, endIndex;
    startIndex = indexStart;
    endIndex = indexEnd;

    current->getSharedBoundary()->setStartIndex( startIndex );
    current->getSharedBoundary()->setEndIndex( endIndex );

    for ( int i = startIndex;
            i < current->getNonSharedBoundary()->getBoundary().size(); ++i )
    {
        current->getSharedBoundary()->getBoundary().append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );

        if ( i == endIndex )
            return;
    }

    for ( int i = 0; i <= endIndex; ++i )
    {
        current->getSharedBoundary()->getBoundary().append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );
    }

    return;
}

void TreeBuilder::identifyBoundaryRange( int* startIndex,
        int* endIndex,
        TreeNode* current, TreeNode* neighbour )
{
    QVector<QPointF> common;
    QPointF lastNeighbour;
    QPointF nextNeighbour;

    switch( Segment::searchType() )
    {
        case DEEP_SEARCH:
            for( int i = 0;
                    i < current->getNonSharedBoundary()->boundarySize();
                    ++i )
            {
                if ( !common.isEmpty() )
                    lastNeighbour = common.last();

                if( neighbour->fullBoundary().contains(
                            current->getNonSharedBoundary()->getBoundary().at( i ) ) )
                {
                    common.append(
                        current->getNonSharedBoundary()->getBoundary().at( i ) );
                    int index = neighbour->fullBoundary().indexOf(
                                    current->getNonSharedBoundary()->getBoundary().at( i ) );
                    lastNeighbour = neighbour->fullBoundary().at( index );
                    nextNeighbour = neighbour->fullBoundary().at(
                                        next( neighbour->fullBoundary(),
                                                      index ) );

                    while ( lastNeighbour == nextNeighbour )
                    {
                        index = index + 1;
                        lastNeighbour = neighbour->fullBoundary().at( index );
                        nextNeighbour = neighbour->fullBoundary().at(
                                            next( neighbour->fullBoundary(),
                                                          index ) );
                    }
                }
                else if( !lastNeighbour.isNull() && !nextNeighbour.isNull() &&
                         NeighbourChecker::isPointOnLine(
                             current->getNonSharedBoundary()->getBoundary().at( i ),
                             lastNeighbour,
                             nextNeighbour ) )
                {
                    neighbour->fullBoundary().insert(
                        next( neighbour->fullBoundary(),
                                      neighbour->fullBoundary().indexOf(
                                          lastNeighbour ) ),
                        current->getNonSharedBoundary()->getBoundary().at( i ) );
                    common.append(
                        current->getNonSharedBoundary()->getBoundary().at( i ) );
                }
            }

            break;

        case SHALLOW_SEARCH:
            for( int i = 0;
                    i < current->getNonSharedBoundary()->boundarySize();
                    ++i )
            {
                if( neighbour->fullBoundary().contains(
                            current->getNonSharedBoundary()->getBoundary().at( i ) ) )
                    common.append(
                        current->getNonSharedBoundary()->getBoundary().at( i ) );
            }
    }

    if ( common.isEmpty() )
        qDebug() << "Common is empty.";

    if ( common.length() == 1 )
        qDebug() << "One Neighbour";

    int longestChain = identifyLongestChain( &common, current );
    *endIndex =
        current->getNonSharedBoundary()->getBoundary().indexOf(
            common.at( longestChain ) );
    *startIndex =
        current->getNonSharedBoundary()->getBoundary().indexOf(
            common.at( next( common, longestChain ) ) );

    return;
}

int TreeBuilder::identifyLongestChain( QVector<QPointF>*
        commonVertices,
        TreeNode* current )
{
    int longest, longestIndex;
    longest = longestIndex = INT_MIN;
    QVector<QPointF> points =
        current->getNonSharedBoundary()->getBoundary();

    if ( isLongestChain( points,
                         points.indexOf( commonVertices->last() ),
                         points.indexOf( commonVertices->first() ),
                         &longest ) )
        longestIndex = commonVertices->size() - 1;

    for ( int i = 0; i < commonVertices->size() - 1; ++i )
    {
        if ( isLongestChain( points,
                             points.indexOf( commonVertices->at( i ) ),
                             points.indexOf( commonVertices->at( i + 1 ) ),
                             &longest ) )
        {
            if ( longest != INT_MIN )
                //badCasesCounter++;
                longestIndex = i;
        }
    }

    return longestIndex;
}


bool TreeBuilder::isLongestChain( QVector<QPointF> current,
                                     int currIndex,
                                     int nextIndex, int* longestL )
{
    int length = nextIndex - currIndex;
    if ( length < 0 )
        length = length + current.size() - 1;
    if ( *longestL < length )
    {
        *longestL = length;
        return true;
    }
    return false;
}


void TreeBuilder::findNonSharedBoundary( TreeNode* current,
        TreeNode* neighbour )
{
    QVector<QPointF> updatedNonSharedBoundary;
    int begin;

    /** If sharedBoundary is the same size as the current NonSharedBoundary,
        then there are no non-shared boundaries. */
    if ( current->getSharedBoundary()->boundarySize() ==
            current->getNonSharedBoundary()->boundarySize() )
    {
        current->initNonSharedBoundary( updatedNonSharedBoundary );
        return;
    }

    begin = current->getSharedBoundary()->getEndIndex();

    /** If current is part of a doughnut case, do not close boundary for
        geographic integrity. */
    if ( neighbour->getNonSharedBoundary()->getBoundary().isEmpty() )
    {
        begin = current->getNonSharedBoundary()->next(
                    begin );
    }

    for ( int i = begin;
            i < current->getNonSharedBoundary()->boundarySize(); ++i )
    {
        if ( i == current->getSharedBoundary()->getStartIndex() )
        {
            if( !neighbour->getNonSharedBoundary()->getBoundary().isEmpty() )
                updatedNonSharedBoundary.append(
                    current->getNonSharedBoundary()->getBoundary().at( i ) );

            current->initNonSharedBoundary( updatedNonSharedBoundary );
            return;
        }

        updatedNonSharedBoundary.append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );
    }

    for ( int i = 0;
            i < current->getSharedBoundary()->getStartIndex();
            ++i )
        updatedNonSharedBoundary.append(
            current->getNonSharedBoundary()->getBoundary().at( i ) );

    /** If current is not part of a doughnut case, close boundary for
        geographic integrity. */
    if( !neighbour->getNonSharedBoundary()->getBoundary().isEmpty() )
        updatedNonSharedBoundary.append(
            current->getNonSharedBoundary()->getBoundary().at(
                current->getSharedBoundary()->getStartIndex() ) );

    current->initNonSharedBoundary( updatedNonSharedBoundary );
    return;
}


void TreeBuilder::updateList( LinkedList* list,
                                 TreeNode* parent,
                                 int neighbour )
{
    list->removeAt( neighbour );
    list->removeFirst();
    addParentToList( list, parent, neighbour );
    return;
}

void TreeBuilder::addParentToList( LinkedList* list,
                                      TreeNode* parent ,
                                      int neighbour )
{
    for ( int i = neighbour; i < list->size(); ++i )
    {
        if( parent->getArea() < list->at( i )->getArea() )
        {
            list->insert( i, *parent );
//            if ( SCZSegment::getDebugMode() )
//                debugRender( list, DEBUG_LINKEDLIST, i, MERGE_CHILD_MULTIPLIER );
            return;
        }
    }

    list->append( *parent );
//    if ( SCZSegment::getDebugMode() )
//        debugRender( list, DEBUG_LINKEDLIST, list->size() - 1,
//                     MERGE_CHILD_MULTIPLIER );

    return;
}

/**
 * @brief SCZTreeBuilder::debugRender send LinkedList to be rendered if debug
 *  rendering is selected.
 * @param list list to render
 * @param debugMode type of debug render to run
 * @param highlight the index of polygon to highlight
 * @param sleepMul rest multiplier after render
 * @return true if successful
 */
bool TreeBuilder::debugRender( LinkedList* list, int debugMode,
                                  int highlight,
                                  int sleepMul )
{
//    if ( Segment::getDebugMode() )
//        Segment::renderer()->renderObject( list, NULL,
//                                              debugMode, highlight,
//                                              sleepMul );

    return true;
}

double TreeBuilder::distance( double range1, double range2 )
{
    return fabs( range1 - range2 );
}

int TreeBuilder::next( QVector<QPointF> list, int index )
{
    if( index == list.size() - 1 )
        return 0;
    else
        return index + 1;
}

double TreeBuilder::lowerBoundSize() const
{
    return m_lowerBoundSize;
}

void TreeBuilder::setLowerBoundSize( double lowerBoundSize )
{
    m_lowerBoundSize = lowerBoundSize;
}

double TreeBuilder::higherBoundSize() const
{
    return m_higherBoundSize;
}

void TreeBuilder::setHigherBoundSize( double higherBoundSize )
{
    m_higherBoundSize = higherBoundSize;
}

int TreeBuilder::getNeighbourType() const
{
    return neighbourType;
}

void TreeBuilder::setNeighbourType( int value )
{
    neighbourType = value;
}

QString TreeBuilder::getRecipeSaveLocation() const
{
    return m_recipeSaveLocation;
}

void TreeBuilder::setRecipeSaveLocation( const QString&
        recipeSaveLocation )
{
    m_recipeSaveLocation = recipeSaveLocation;
}

QString TreeBuilder::getRecipeLoadLocation() const
{
    return m_recipeLoadLocation;
}

void TreeBuilder::setRecipeLoadLocation( const QString&
        recipeLoadLocation )
{
    m_recipeLoadLocation = recipeLoadLocation;
}

QVector<CrfRow>* TreeBuilder::getLoadedRecipe() const
{
    return m_loadedRecipe;
}

void TreeBuilder::setLoadedRecipe( QVector<CrfRow>*
                                      loadedRecipe )
{
    m_loadedRecipe = loadedRecipe;
}

int TreeBuilder::getCalculationType() const
{
    return calculationType;
}

void TreeBuilder::setCalculationType( int value )
{
    calculationType = value;
}

int TreeBuilder::getRecipeType() const
{
    return recipeType;
}

void TreeBuilder::setRecipeType( int value )
{
    recipeType = value;
}

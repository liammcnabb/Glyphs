#ifndef MAININTERFACEWINDOW_H
#define MAININTERFACEWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStandardItem>

#include "LM/shpreader.h"
#include "LM/csvreader.h"
#include "map.h"
#include "gridamalgamate.h"

namespace Ui {
class MainInterfaceWindow;
}

class MainInterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief RANGE_LEAF Range set by all leaf nodes
     */
    static const int RANGE_LEAF = 0;
    /**
     * @brief RANGE_SHOWN Range set by shown areas only
     */
    static const int RANGE_SHOWN = 1;

    /**
     * @brief RANGE_PER_VALUE Each dimension is given it's own value range
     */
    static const int RANGE_PER_VALUE = 0;
    /**
     * @brief RANGE_OVERALL Each dimension has a range pertaining all values
     */
    static const int RANGE_OVERALL = 1;

    /**
     * @brief MainInterfaceWindow Default Constructor
     * @param parent
     */
    explicit MainInterfaceWindow(QWidget *parent = 0);
    ~MainInterfaceWindow();

    /**
     * @brief getFullHierarchies getter method for full hierarchies from Map.h
     * @return list of full TreeNode hierarchies
     */
    QVector<TreeNode> getFullHierarchies() const;
    /**
     * @brief setFullHierarchies setter method for full hierarchies
     * @param fullHierarchies list of full TreeNode hierarchies
     */
    void setFullHierarchies(const QVector<TreeNode> &fullHierarchies);

    /**
     * @brief getValueHeaders getter method for data value headers extracted
     * from data
     * @return lists of headers
     */
    QStringList getValueHeaders() const;
    /**
     * @brief setValueHeaders setter method for data value headers extracted
     * from data
     * @param valueHeaders list of headers
     */
    void setValueHeaders(const QStringList &valueHeaders);

    /**
     * @brief getPreviousVirtualZoomValue getter method holds the previous value of the
     * virtual zoom. Used to check whether areas are added or removed from the
     * canvas to enable transitions
     * @return value of last recorded zoom value
     */
    int getPreviousVirtualZoomValue() const;
    /**
     * @brief setPreviousVirtualZoomValue setter method holds the previous value of the
     * virtual zoom. Used to check whether areas are added or removed from the
     * canvas to enable transitions
     * @param value newly last recorded virtual zoom value
     */
    void setPreviousVirtualZoomValue(int value);

    /**
     * @brief getLeafMins getter method for the minimum values of the leaf data
     * points
     * @return a vector of the minimum values for leaf nodes
     */
    QVector<float> getLeafMins() const;
    /**
     * @brief setLeafMins setter method for the minimum values of the leaf data
     * points
     * @param leafMins new values for minimums of all leaf nodes
     */
    void setLeafMins(const QVector<float> &leafMins);

    /**
     * @brief getLeafMaxes getter method for the maximum values of the leaf data
     * points
     * @return  a vector of the maximum values for leaf nodes
     */
    QVector<float> getLeafMaxes() const;
    /**
     * @brief setLeafMaxes setter method for the maximum values of the leaf data
     * points
     * @param leafMaxes new values for maximums of all leaf nodes
     */
    void setLeafMaxes(const QVector<float> &leafMaxes);

    /**
     * @brief getRangeBreadth getter method for current option for range breadth
     * mapping.
     * @see MainInterfaceWindow::RANGE_LEAF
     * @see MainInterfaceWindow::RANGE_SHOWN
     * @return current selected option for range breadth mapping
     */
    int getRangeBreadth() const;
    /**
     * @brief setRangeBreadth setter method for current option for range breadth
     * mapping.
     * @see MainInterfaceWindow::RANGE_LEAF
     * @see MainInterfaceWindow::RANGE_SHOWN
     * @param rangeBreadth new selected value for range breadth mapping
     */
    void setRangeBreadth(int rangeBreadth);

    /**
     * @brief getRangeDepth getter method for current option of range depth
     * mapping
     * @see MainInterfaceWindow::RANGE_PER_VALUE
     * @see MainInterfaceWindow::RANGE_OVERALL
     * @return current selected option for range depth mapping
     */
    int getRangeDepth() const;
    /**
     * @brief setRangeDepth setter method for current option of range depth
     * mapping
     * @see MainInterfaceWindow::RANGE_PER_VALUE
     * @see MainInterfaceWindow::RANGE_OVERALL
     * @param rangeDepth new selected value for range depth mapping
     */
    void setRangeDepth(int rangeDepth);

    /**
     * @brief getSaved getter method for flag to set values some values that
     * should only be saved during a first passthrough
     * @return saved flag state
     */
    bool getSaved() const;
    /**
     * @brief setSaved setter method for flag to set values some values that
     * should only be saved during a first passthrough
     * @param saved new value depicting saved flag state
     */
    void setSaved(bool saved);

    /**
     * @brief calculateOverallRange calculates the overall minimum and maximum
     * value of the calculated values
     * @param mins the minimum value per dimension
     * @param maxes the maximmum value per dimension
     */
    void calculateOverallRange(QVector<float> mins, QVector<float> maxes);
    /**
     * @brief getValueFilters getter method for mapping states of each
     * dimension. True signifies checkbox is checked, false signifies checkbox
     * is unchecked.
     * @return  list of booleans relating to each data header
     */
    QVector<bool> getValueFilters() const;
    /**
     * @brief setValueFilters setter method for mapping states of each
     * dimension. True signifies checkbox is checked, false signifies checkbos
     *  is unchecked.
     * @param valueFilters new values pertaining to checkboxes for data valu
     * e filters
     */
    void setValueFilters(const QVector<bool> &valueFilters);
    /**
     * @brief getGridValues getter method holding the values for each section
     * of the grid view
     * @return vector of polygons depicting values for each grid cell
     */
    QVector<Polygon> getGridValues() const;
    /**
     * @brief setGridValues setter method holding the values for each section
     * of the grid view
     * @param gridValues new set of polygon depicting values for each grid cell
     */
    void setGridValues(const QVector<Polygon> &gridValues);

private slots:
    /**
     * @brief on_actionOpen_triggered Open functionality to begin procedure
     */
    void on_actionOpen_triggered();

    /**
     * @brief on_rdo_DebugCentroids_released default mappping of glyphs
     */
    void on_rdo_DebugCentroids_released();

    /**
     * @brief on_rdo_EqualSegmentPie_released wheel glyph mapping of glyphs
     */
    void on_rdo_EqualSegmentPie_released();

    /**
     * @brief on_rdo_VariableSegmentPie_released pie chart mapping of glyphs
     */
    void on_rdo_VariableSegmentPie_released();

    /**
     * @brief on_virtualzoom_valueChanged action used to modify the virtual zoom
     * value
     * @param value the new value depicted on the slider
     */
    void on_virtualzoom_valueChanged(int value);

    /**
     * @brief on_GlyphSize_valueChanged action used to modify the glyph size
     * @param value new value depicted by the glyph size slider
     */
    void on_GlyphSize_valueChanged(int value);

    /**
     * @brief on_actionDebugMousePointer_toggled action to show debug moouse
     * pointer tracker on canvas
     * @param arg1 bool depicting whether debug option is active
     */
    void on_actionDebugMousePointer_toggled(bool arg1);

    /**
     * @brief on_rdo_StarGlyph_released option to show star glyph mapping
     */
    void on_rdo_StarGlyph_released();

    /**
     * @brief on_lstHeaders_doubleClicked action used to change display of debug
     * centroids glyph mapping to different value header
     * @param index index to map to color in debug centroids mapping
     */
    void on_lstHeaders_doubleClicked(const QModelIndex &index);

    /**
     * @brief on_AreaOpacity_valueChanged action to change opacity of mapped
     * size color to depicted areas
     * @param value the new opacity value from the slider
     */
    void on_AreaOpacity_valueChanged(int value);

    /**
     * @brief on_chkColoredStarLines_toggled action to map color to star glyph
     * lines
     * @param checked boolean depicting toggle state of colored star lines
     * option
     */
    void on_chkColoredStarLines_toggled(bool checked);

    /**
     * @brief on_rdoOutline_released option to map hidden area indicator to
     * outline
     */
    void on_rdoOutline_released();

    /**
     * @brief on_rdoSize_released option to map hidden area indicator to size
     */
    void on_rdoSize_released();

    /**
     * @brief on_rdoRings_released option to map hidden area indicator to shadow
     */
    void on_rdoRings_released();

    /**
     * @brief on_rdoOutlineSize_released option to map hidden area indicator to
     * size+outline
     */
    void on_rdoOutlineSize_released();

    /**
     * @brief on_rdo_Bar_released option to map bar charts as glyphs
     */
    void on_rdo_Bar_released();

    /**
     * @brief on_verticalSlider_valueChanged action to modify the zoom of the
     * canvas
     * @param value the new zoom value level
     */
    void on_verticalSlider_valueChanged(int value);

    /**
     * @brief on_btnAutomatic_released action to estimate the ideal glyph
     * placement using the glyph size
     */
    void on_btnAutomatic_released();

    /**
     * @brief on_actionShow_Extents_toggled debug option to display the glyph
     * extents for glyphs
     * @param arg1 toggle state of option
     */
    void on_actionShow_Extents_toggled(bool arg1);

    /**
     * @brief on_rdoRangebyLeaf_released option to map data ranges based on
     * leaf nodes only
     */
    void on_rdoRangebyLeaf_released();

    /**
     * @brief on_rdoRangeOfShown_released option to map data ranges based on
     * visible areas only
     */
    void on_rdoRangeOfShown_released();

    /**
     * @brief on_rdoCalcPerValue_released option to map data ranges per data
     * dimension
     */
    void on_rdoCalcPerValue_released();

    /**
     * @brief on_rdoCalcOverall_released option to map data ranges through all
     * dimensions
     */
    void on_rdoCalcOverall_released();

    /**
     * @brief on_lstHeaders_clicked action to turn header filters on/off
     * @param index index of clicked header
     */
    void on_lstHeaders_clicked(const QModelIndex &index);

    /**
     * @brief on_toolButton_released action to select colormap 1
     */
    void on_toolButton_released();

    /**
     * @brief on_toolButton_released action to select colormap 2
     */
    void on_toolButton_2_released();

    /**
     * @brief on_toolButton_released action to select colormap 3
     */
    void on_toolButton_3_released();

    /**
     * @brief on_toolButton_released action to select colormap 4
     */
    void on_toolButton_4_released();

    /**
     * @brief on_toolButton_released action to select colormap 5
     */
    void on_toolButton_5_released();

    /**
     * @brief on_toolButton_released action to select colormap 6
     */
    void on_toolButton_6_released();

    /**
     * @brief on_toolButton_released action to select colormap 7
     */
    void on_toolButton_7_released();
    /**
     * @brief on_chkMatchingLines_toggled option to assign matching colors
     * to the hidden area indicator
     * @param checked current state of this option
     */
    void on_chkMatchingLines_toggled(bool checked);

    /**
     * @brief on_rdoFC1_released option to set value filter to "remove mapping"
     * state
     */
    void on_rdoFC1_released();

    /**
     * @brief on_rdoFC2_released option to set value filter to "focus+context"
     * state
     */
    void on_rdoFC2_released();

    /**
     * @brief on_actionGrid_Placement_toggled option to toggle grid placement
     * view
     * @param arg1 toggle state
     */
    void on_actionGrid_Placement_toggled(bool arg1);

    /**
     * @brief on_radioButton_4_released option to present an advanced filter off
     */
    void on_radioButton_4_released();

    /**
     * @brief on_radioButton_2_released option to present an andavnced filter to
     * above average focus+context options
     */
    void on_radioButton_2_released();

    /**
     * @brief on_radioButton_3_released option to present an advanced filter to
     * below average focus+context options
     */
    void on_radioButton_3_released();

private:
    Ui::MainInterfaceWindow *ui;
    int ignoredValues = 4;
    QVector<TreeNode> m_fullHierarchies;
    QStringList m_valueHeaders;
    int previousVirtualZoomValue = 0;

    /**
     * @brief visibleNodes method used to gather the nodes that should be
     * displayed on the canvas
     * @param minScreenSpace designated minimum screen space to test against
     * @param node current data structure to gather from
     * @return a vector of dislayed areas
     */
    QVector<TreeNode> visibleNodes(double minScreenSpace, TreeNode node);
    /**
     * @brief visibleNodes method used to gather the nodes that should be
     * displayed on the canvas
     * @see MainInterfaceWindow::visibleNodes(double minScreenSpace, TreeNode node)
     * @param minScreenSpace designated minimum screen space to test against
     * @param node current data structure to gather from
     * @param currentList currently gathered area
     */
    void visibleNodes(double minScreenSpace, TreeNode *node,
                      QVector<TreeNode> *currentList);
    /**
     * @brief declareVisiblePolygons gathers all nodes to be displayed on the
     * canvas throughout all hierarchical data structures
     * @param list list of hierarchical data structures
     * @param minScreenSpace designated minimum screen space to test against
     * @return a vector of all displayed areas
     */
    QVector<TreeNode> declareVisiblePolygons(QVector<TreeNode> list,
                                             double minScreenSpace);
    /**
     * @brief calculateStandardDeviation calculated the average values
     * @param list vector of TreeNodes
     */
    void calculateStandardDeviation(QVector<TreeNode> list);
    /**
     * @brief splitVisible splits list of visible areas in transition groups,
     * neutral, add and removed
     * @param list vector of unsorted TreeNodes
     */
    void splitVisible(QVector<TreeNode> list);

    /**
     * @brief initializeTable Initialize the header value table
     * @param list list of data value headers
     */
    void initializeTable(QStringList list);
    /**
     * @brief calculateNewlyVisible starting method to start selecting which
     * areas need to be displayed
     * @param screenSpaceValue the minimum spcae value for areas to be presented
     */
    void calculateNewlyVisible(int screenSpaceValue);
    QStringListModel model;
    QVector<float> m_leafMins;
    QVector<float> m_leafMaxes;
    QVector<Polygon> m_gridValues;

    int m_rangeBreadth = 0;
    int m_rangeDepth = 0;

    bool m_saved = false;

    QVector<bool> m_valueFilters;
};

#endif // MAININTERFACEWINDOW_H

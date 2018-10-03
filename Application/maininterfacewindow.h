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

namespace Ui {
class MainInterfaceWindow;
}

class MainInterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const int RANGE_LEAF = 0;
    static const int RANGE_SHOWN = 1;

    static const int RANGE_PER_VALUE = 0;
    static const int RANGE_OVERALL = 1;

    explicit MainInterfaceWindow(QWidget *parent = 0);
    ~MainInterfaceWindow();

    QVector<TreeNode> getFullHierarchies() const;
    void setFullHierarchies(const QVector<TreeNode> &fullHierarchies);



    QStringList getValueHeaders() const;
    void setValueHeaders(const QStringList &valueHeaders);

    int getPreviousVirtualZoomValue() const;
    void setPreviousVirtualZoomValue(int value);

    QVector<float> getLeafMins() const;
    void setLeafMins(const QVector<float> &leafMins);

    QVector<float> getLeafMaxes() const;
    void setLeafMaxes(const QVector<float> &leafMaxes);

    int getRangeBreadth() const;
    void setRangeBreadth(int rangeBreadth);

    int getRangeDepth() const;
    void setRangeDepth(int rangeDepth);

    bool getSaved() const;
    void setSaved(bool saved);

    void calculateOverallRange(QVector<float> mins, QVector<float> maxes);
    QVector<bool> getValueFilters() const;
    void setValueFilters(const QVector<bool> &valueFilters);

private slots:
    void on_actionEngland_Example_triggered();

    //    void on_lstHeaders_itemDoubleClicked(QListWidgetItem *item);


    void on_rdo_DebugCentroids_released();

    void on_rdo_EqualSegmentPie_released();

    void on_rdo_VariableSegmentPie_released();

    void on_virtualzoom_valueChanged(int value);

    void on_GlyphSize_valueChanged(int value);

    void on_actionDebugMousePointer_toggled(bool arg1);

    void on_rdo_StarGlyph_released();

    void on_lstHeaders_doubleClicked(const QModelIndex &index);

    void on_AreaOpacity_valueChanged(int value);

    void on_chkColoredStarLines_toggled(bool checked);


    void on_rdoOutline_released();

    void on_rdoSize_released();

    void on_rdoRings_released();

    void on_rdoOutlineSize_released();

    void on_radioButton_released();

    void on_verticalSlider_valueChanged(int value);

    void on_btnAutomatic_released();

    void on_actionShow_Extents_toggled(bool arg1);

    void on_rdoRangebyLeaf_released();

    void on_rdoRangeOfShown_released();

    void on_rdoCalcPerValue_released();

    void on_rdoCalcOverall_released();

    void on_lstHeaders_clicked(const QModelIndex &index);
private:
    Ui::MainInterfaceWindow *ui;
    int ignoredValues = 4;
    QVector<TreeNode> m_fullHierarchies;
    QStringList m_valueHeaders;
    int previousVirtualZoomValue = 0;

    QVector<TreeNode> visibleNodes(double minScreenSpace, TreeNode node);
    void visibleNodes(double minScreenSpace, TreeNode *node, QVector<TreeNode> *currentList);
    QVector<TreeNode> declareVisiblePolygons(QVector<TreeNode> list, double minScreenSpace);
    void calculateStandardDeviation(QVector<TreeNode> list);
    void splitVisible(QVector<TreeNode> list);
    QStringListModel model;
    void initializeTable(QStringList list);
    void calculateNewlyVisible(int screenSpaceValue);

    QVector<float> m_leafMins;
    QVector<float> m_leafMaxes;

    int m_rangeBreadth = 0;
    int m_rangeDepth = 0;

    bool m_saved = false;

    QVector<bool> m_valueFilters;
};

#endif // MAININTERFACEWINDOW_H

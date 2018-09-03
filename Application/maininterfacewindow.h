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
    explicit MainInterfaceWindow(QWidget *parent = 0);
    ~MainInterfaceWindow();

    QVector<TreeNode> getFullHierarchies() const;
    void setFullHierarchies(const QVector<TreeNode> &fullHierarchies);

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

private:
    Ui::MainInterfaceWindow *ui;
    int ignoredValues = 4;
    QVector<TreeNode> m_fullHierarchies;

    QVector<TreeNode> visibleNodes(double minScreenSpace, TreeNode node);
    void visibleNodes(double minScreenSpace, TreeNode *node, QVector<TreeNode> *currentList);
    QVector<TreeNode> declareVisiblePolygons(QVector<TreeNode> list, double minScreenSpace);
    void calculateStandardDeviation(QVector<TreeNode> list);
    void splitVisible(QVector<TreeNode> list);
    QStringListModel model;
    void initializeTable(QStringList list);
};

#endif // MAININTERFACEWINDOW_H

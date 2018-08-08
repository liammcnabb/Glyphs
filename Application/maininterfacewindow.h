#ifndef MAININTERFACEWINDOW_H
#define MAININTERFACEWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <QListWidgetItem>

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

    void on_lstHeaders_itemDoubleClicked(QListWidgetItem *item);


    void on_rdo_DebugCentroids_released();

    void on_rdo_EqualSegmentPie_released();

    void on_rdo_VariableSegmentPie_released();

    void on_virtualzoom_valueChanged(int value);

private:
    Ui::MainInterfaceWindow *ui;
    int ignoredValues = 4;
    QVector<TreeNode> m_fullHierarchies;

    QVector<TreeNode> visibleNodes(double minScreenSpace, TreeNode node);
    void visibleNodes(double minScreenSpace, TreeNode *node, QVector<TreeNode> *currentList);
    QVector<TreeNode> declareVisiblePolygons(QVector<TreeNode> list, double minScreenSpace);
};

#endif // MAININTERFACEWINDOW_H

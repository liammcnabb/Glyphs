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

private slots:
    void on_actionEngland_Example_triggered();

    void on_lstHeaders_itemDoubleClicked(QListWidgetItem *item);


    void on_rdo_DebugCentroids_released();

    void on_rdo_EqualSegmentPie_released();

    void on_rdo_VariableSegmentPie_released();

private:
    Ui::MainInterfaceWindow *ui;
    int ignoredValues = 4;
};

#endif // MAININTERFACEWINDOW_H

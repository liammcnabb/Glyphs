#ifndef MAININTERFACEWINDOW_H
#define MAININTERFACEWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include "LM/shpreader.h"

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

private:
    Ui::MainInterfaceWindow *ui;
};

#endif // MAININTERFACEWINDOW_H

#pragma once

#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Invoked when user pushes "Add" button.
    void addPayment();

    // Invoked when user picks an item from payment list.
    void editPayment(QListWidgetItem* currentItem);

    // Invoked when user clicks "Remove" button.
    void removePayment();

    // Invoked when user pushes "Summary" button.
    void createSummary();
};

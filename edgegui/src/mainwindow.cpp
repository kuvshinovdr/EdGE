#include "mainwindow.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);

    viewModel_.setNodeCountListener([this](std::size_t count) { emit nodeCountChanged(count); });
}

MainWindow::~MainWindow() = default;

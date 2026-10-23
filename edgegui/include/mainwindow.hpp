#ifndef EDGEGUI_MAINWINDOW_HPP
#define EDGEGUI_MAINWINDOW_HPP

#include "viewmodels/graph_view_model.hpp"

#include <cstddef>
#include <memory>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// View: passive, forwards user actions to the ViewModel and mirrors its state.
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

signals:
    void nodeCountChanged(std::size_t count);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    GraphViewModel viewModel_;
};

#endif//EDGEGUI_MAINWINDOW_HPP

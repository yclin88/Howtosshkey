#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSpinBoxValueChanged(int value);
    void onSliderValueChanged(int value);

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *spinBoxLayout;
    QHBoxLayout *sliderLayout;
    
    QLabel *spinBoxLabel;
    QSpinBox *spinBox;
    QLabel *sliderLabel;
    QSlider *slider;
    QLabel *valueLabel;
    
    void setupUI();
    void connectSignals();
};

#endif // MAINWINDOW_H
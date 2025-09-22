#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , mainLayout(nullptr)
    , spinBoxLayout(nullptr)
    , sliderLayout(nullptr)
    , spinBoxLabel(nullptr)
    , spinBox(nullptr)
    , sliderLabel(nullptr)
    , slider(nullptr)
    , valueLabel(nullptr)
{
    setupUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
    // Qt handles cleanup automatically due to parent-child relationships
}

void MainWindow::setupUI()
{
    // Create central widget and main layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    // Create SpinBox section
    spinBoxLayout = new QHBoxLayout();
    spinBoxLabel = new QLabel("SpinBox:", this);
    spinBox = new QSpinBox(this);
    spinBox->setRange(0, 100);
    spinBox->setValue(50);
    
    spinBoxLayout->addWidget(spinBoxLabel);
    spinBoxLayout->addWidget(spinBox);
    spinBoxLayout->addStretch();
    
    // Create Slider section
    sliderLayout = new QHBoxLayout();
    sliderLabel = new QLabel("Slider:", this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 100);
    slider->setValue(50);
    
    sliderLayout->addWidget(sliderLabel);
    sliderLayout->addWidget(slider);
    
    // Create value display label
    valueLabel = new QLabel("Current Value: 50", this);
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: blue;");
    
    // Add all layouts to main layout
    mainLayout->addLayout(spinBoxLayout);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addWidget(valueLabel);
    mainLayout->addStretch();
    
    // Set window properties
    setWindowTitle("SpinBox and Slider Communication Demo");
    setMinimumSize(400, 200);
    resize(500, 250);
}

void MainWindow::connectSignals()
{
    // Connect SpinBox value change to slot and slider
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onSpinBoxValueChanged);
    
    // Connect Slider value change to slot and spinbox
    connect(slider, &QSlider::valueChanged,
            this, &MainWindow::onSliderValueChanged);
}

void MainWindow::onSpinBoxValueChanged(int value)
{
    // Update slider value without triggering its signal
    slider->blockSignals(true);
    slider->setValue(value);
    slider->blockSignals(false);
    
    // Update value display
    valueLabel->setText(QString("Current Value: %1").arg(value));
}

void MainWindow::onSliderValueChanged(int value)
{
    // Update spinbox value without triggering its signal
    spinBox->blockSignals(true);
    spinBox->setValue(value);
    spinBox->blockSignals(false);
    
    // Update value display
    valueLabel->setText(QString("Current Value: %1").arg(value));
}
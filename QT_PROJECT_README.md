# Qt SpinBox-Slider Communication Demo

This Qt application demonstrates signal/slot communication between a QSpinBox and QSlider widget. Users can interact with either widget to adjust an integer value, and both widgets will stay synchronized through Qt's signal/slot mechanism.

## Features

- **QSpinBox**: Allows direct numerical input and adjustment with increment/decrement buttons
- **QSlider**: Provides visual slider interface for value selection
- **Real-time synchronization**: Changes in either widget immediately update the other
- **Value display**: Shows current value in a centered label
- **Range**: Values from 0 to 100 (customizable in code)

## Technical Implementation

### Signal/Slot Connections

The application uses Qt's signal/slot mechanism to connect the widgets:

```cpp
// SpinBox value changes update the slider
connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        this, &MainWindow::onSpinBoxValueChanged);

// Slider value changes update the spinbox
connect(slider, &QSlider::valueChanged,
        this, &MainWindow::onSliderValueChanged);
```

### Preventing Signal Loops

To prevent infinite signal loops when one widget updates the other, the application uses `blockSignals()`:

```cpp
void MainWindow::onSpinBoxValueChanged(int value)
{
    // Update slider without triggering its signal
    slider->blockSignals(true);
    slider->setValue(value);
    slider->blockSignals(false);
    
    // Update display
    valueLabel->setText(QString("Current Value: %1").arg(value));
}
```

## Building and Running

### Prerequisites

- Qt5 development libraries
- C++11 compatible compiler (g++, clang++)
- qmake build system

### Ubuntu/Debian Installation

```bash
sudo apt update
sudo apt install qt5-qmake qtbase5-dev qtbase5-dev-tools build-essential
```

### Build Instructions

1. Clone or download this repository
2. Navigate to the project directory
3. Generate the Makefile:
   ```bash
   qmake SpinBoxSliderApp.pro
   ```
4. Compile the application:
   ```bash
   make
   ```
5. Run the executable:
   ```bash
   ./SpinBoxSliderApp
   ```

### Clean Build

To clean build artifacts:
```bash
make clean
rm -f Makefile .qmake.stash
```

## Project Structure

```
├── SpinBoxSliderApp.pro    # Qt project file
├── main.cpp                # Application entry point
├── mainwindow.h            # Main window header
├── mainwindow.cpp          # Main window implementation
├── .gitignore              # Git ignore rules
└── QT_PROJECT_README.md    # This documentation
```

## Code Overview

### main.cpp
Simple Qt application setup with MainWindow instantiation.

### mainwindow.h
Declares the MainWindow class with:
- Widget member variables (QSpinBox, QSlider, QLabel)
- Layout management
- Slot methods for handling value changes

### mainwindow.cpp
Implements:
- UI setup with proper layout management
- Signal/slot connections
- Value synchronization logic
- Window properties and styling

## Customization

### Changing Value Range
Modify the range in `setupUI()`:
```cpp
spinBox->setRange(0, 1000);  // Min: 0, Max: 1000
slider->setRange(0, 1000);
```

### Changing Initial Value
Modify the default value:
```cpp
spinBox->setValue(250);
slider->setValue(250);
```

### Styling
The value label includes basic styling. Extend in `setupUI()`:
```cpp
valueLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: red; background-color: yellow;");
```

## Learning Objectives

This example demonstrates:
1. **Qt Signal/Slot mechanism**: Core Qt communication paradigm
2. **Widget synchronization**: Keeping multiple UI elements in sync
3. **Signal blocking**: Preventing infinite loops in bidirectional connections
4. **Layout management**: Organizing widgets with QVBoxLayout and QHBoxLayout
5. **Qt project structure**: Basic .pro file and multi-file organization

## License

This is a demonstration project. Feel free to use and modify as needed.
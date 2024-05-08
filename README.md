# Solar Power Management System

The Solar Power Management System is a powerful tool that allows you to manage and monitor a solar power system. It's written in Arduino C and can control relays to manage power flow and display system information on an LCD.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Known Bugs](#bugs)
- [Contributing](#contributing)
- [License](#license)

## Installation

To install the Solar Power Management System, you need to upload the Arduino sketch to your Arduino board. You will need the `LiquidCrystal` library installed in your Arduino IDE.

1. Connect your Arduino board to your computer.
2. Open the Arduino IDE.
3. Open the sketch file.
4. Click on `Sketch > Include Library > Manage Libraries...` in the Arduino IDE menu.
5. In the Library Manager, search for `LiquidCrystal` and install it.
6. Click on `Sketch > Upload` to upload the sketch to your Arduino board.

## Usage

After uploading the sketch, the system will start monitoring the solar power system and displaying information on the LCD. The system will manage the power flow between the solar cells, the battery, and the load based on the current conditions.

The LCD will display the following information:

- The current power consumption of the load in Amps.
- The current power production of the solar cells in Amps.
- The current status of the battery (charging, discharging, or idle).

## Bugs

Currently, there are no known bugs. If you find any, please open an issue in the GitHub repository.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)

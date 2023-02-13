# Wokwi 104GT-2 Chip Example

This is a basic custom chip for [Wokwi](https://wokwi.com/). It implements a 104GT-2 thermistor with a 4.7k pull up resistor

## Pin names

| Name | Description              |
| ---- | ------------------------ |
| SIG  | Output analogue signal   |
| GND  | Ground                   |
| VCC  | Supply voltage           |

## Usage

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
  "dependencies": {
    "chip-104GT-2": "github:alextrical/WOKWI-104GT-2-CUSTOM-chip@1.0.0"
  }
```

Then, add the chip to your circuit by adding a `chip-104GT-2` item to the `parts` section of diagram.json:

```json
  "parts": {
    ...,
    { "type": "chip-104GT-2", "id": "chip1" }
  },
```

For a complete example, see [the 104GT-2 chip test project](https://wokwi.com/projects/356569010110140417).

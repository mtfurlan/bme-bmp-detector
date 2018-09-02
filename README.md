# TEST IF YOUR SENSOR IS A BME280 OR A BMP280
The issues getting a bme280 off ebay has [well known problems](https://goughlui.com/2018/08/05/note-bosch-sensortec-bmp280-vs-bme280-sensor-confusion/), in that you always get the bmp280.
This will detect if a thing is a BME280 or a BMP280, and print it to an OLED, and hopefully make the process of getting your money back easier.

Install platformio core and either figure out `pio run`, or just do `make flash`.

There is an issue where it freezes after you plug in a bmp280, not sure what's up with that. Just reset it.

## Images
![detector with bme][/img/bme.jpg?raw=true]
![detector with bmp][/img/bmp.jpg?raw=true]

## Connections
* D1 mini SCL: D1
* D1 mini SDA: D2

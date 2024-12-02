# HomeIoT

## Introduction

This project is a simple home automation system with a lot of flexibility. The system is built on an ESP32 and uses a builtin webserver to control the devices. The devices can be added dynamically and the system will remember the state of the devices even after a power loss. The system is built with a lot of flexibility in mind and can be easily extended with new devices.

## Features

-   Webserver for controlling devices

-   Dynamic device adding

-   Device state is saved when changed so it will be remembered after a
    power loss or restart

-   Easily extendable with new devices. **This will be done through an Android app that will be able to add new devices to the system. This can also be done using a post request.**

## Devices

-   **Relay**

    -   A simple relay that can be turned on and off

-   **Temperature and Humidity sensor**

    -   A sensor that can measure the temperature and humidity

-   **RTC Module**

    -   A real time clock that can be used to keep track of time for devices that need timer and alarm functionality.

-   **OLED Display**
    -   A display that can be used to show system statistics or other information.

### Future devices

-   **RGB LED**

    -   An RGB LED that can be controlled with the system

-   **Stepper Motor**

    -   A stepper motor that can be controlled with the system

-   **PIR Sensor**
    -   A PIR sensor that can be used to detect motion

## Future features

-   **Android app for adding new devices**

    -   An [Android app](https://github.com/jetsup/Home-IoT-Android.git) that can be used to add new devices to the system. The app will then send a post request to the system with the device information.

-   **Rate limiting**

    -   Rate limiting for the system to prevent spamming and possible DOS attacks.

-   **Voice control**
    -   Voice control for the system. This will be done using Google Assistant or Alexa.

## Installation

1. Clone the repository
    ```bash
     git clone https://github.com/jetsup/HomeIoT.git
    ```
2. Copy the file [include/HomeCredentials.example.hpp](include/HomeCredentials.example.hpp) to `include/HomeCredentials.hpp` and fill in the required information for your network.
    ```cpp
    // Network
    #define HOME_WIFI_SSID "SSID"
    #define HOME_WIFI_PASSWORD "PASSWORD"
    #define HOME_DEVICE_DNS_NAME "DNS_NAME"
    ```
3. Navigate to the project folder in your terminal
    ```bash
    cd HomeIoT
    ```
4. Build the project
    ```bash
    platformio run
    ```
5. Upload the project to the ESP32
    ```bash
    platformio run --target upload
    ```
6. Open the serial monitor
    ```bash
    platformio device monitor
    ```

## Usage

1. Connect to the WiFi network with the SSID and password you provided in the `HomeCredentials.hpp` file.

2. Open a browser and navigate to the DNS name you provided in the `HomeCredentials.hpp` file.

3. You should now be able to use **GET** and **POST** requests to control the devices and add new devices.

4. Use this [Android app](https://github.com/jetsup/Home-IoT-Android.git) for seamless control and administration of the system.

## Resources

-   To convert the image to a byte array I used the [image2cpp](https://javl.github.io/image2cpp/) tool.

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

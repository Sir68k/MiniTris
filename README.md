# MiniTris

A simple tetris game for Sony NetMD portables, currently targetting **Type-S NetMD (CXD2678, CXD2680)** devices with single row displays. 

This application serves as a template project for building code for the Sony NetMD portables, while also demonstrating the results from the firmware reverse engineering efforts (see https://github.com/Sir68k/md-firmware).

# Demo

[![Demo](https://img.youtube.com/vi/IWdc0CjOyqo/0.jpg)](https://www.youtube.com/watch?v=IWdc0CjOyqo)
## Working devices

Developed with a MZ-N520, confirmed working on an MZ-N710.

## Compatibilty

__Type-S (CXD2678, CXD2680) devices:__
- The build directory contains builds for firmwares S1.0, S1.1, S1.3, S1.4, S1.5, and S1.6. Firmwares S1.2 is currently unsupported as no devices running it have been encountered. If you have a device with firmware version S1.2, please dump your firmware using https://web.minidisc.wiki/ and contact us!

__Type-R (CXD2677) devices:__
- No support yet, maybe be added in the future.

## Running

### Easy method

MiniTris is built-in Web MiniDisc Pro (https://web.minidisc.wiki/) and you can launch it directly from the factory mode! Press "Prev" to start the game. During the game you can press "Menu" to exit (it will restart the device).

### Manual method

The correct hex build (hex_builds/minitris_yourversion.hex) needs to be loaded to `0x02005500` in memory and then executed. Asivery's NetMD IDE supports loading uploading raw hex data to a particular memory offset and executing it (https://github.com/asivery/netmd-asm-ide).


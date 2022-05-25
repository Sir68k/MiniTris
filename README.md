# MiniTris

A simple tetris game for Sony NetMD portables, currently targetting **v1.6 CXD2680** devices with single row displays. 

This application serves as a template project for building code for the Sony NetMD portables, while also demonstrating the results from the firmware reverse engineering efforts (see https://github.com/Sir68k/md-firmware).

# Demo

[![Demo](https://img.youtube.com/vi/IWdc0CjOyqo/0.jpg)](https://www.youtube.com/watch?v=IWdc0CjOyqo)
## Working devices

Developed with a MZ-N520, confirmed working on an MZ-N710.

## Running

This binary (build/minitris.bin) needs to be loaded to `0x02005500` in memory and then executed. Asivery's NetMD IDE supports loading uploading raw hex data to a particular memory offset and executing it (https://github.com/asivery/netmd-asm-ide).

Press "Prev" to start the game. During the game you can press "Menu" to exit (it will restart the device).

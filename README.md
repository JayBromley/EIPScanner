# EIPScanner

[![Build Status](https://travis-ci.com/nimbuscontrols/EIPScanner.svg?branch=master)](https://travis-ci.com/nimbuscontrols/EIPScanner)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/nimbuscontrols/EIPScanner)


Free implementation of Ethernet/IP scanner in C++.


## Features

* Explicit messaging
* Implicit messaging (only point-to-point)
* Discovery

CIP Standard objects:

* File Object (upload only)
* Parameter Object (read only)
* Identity Object

Vendor specific objects:

* RA DPI Fault Object 

## Requirements

* CMake 3.5 and higher
* C++20 compiler (tested with GCC and MinGW)
* Linux, MacOS, and Windows

## Installing

```shell
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --target install
```

## Usage

To see how to work with the library, look into `examples` directory 

## Notes on using with multiple Ethernet/IP devices

As the current library is written, it is *not* possible to connect to multiple
Ethernet/IP devices from a single client machine. This is because all devices
use the same ports (explicit 44818, implicit 2222) for their connections. As 
this library does not multiplex the client port, connecting to two different 
Ethernet/IP devices on the same machine, even if from different processes, will
fail.

To resolve this problem. The option of specifying a local IP address to use for
the communication port has been added. This allows a machine with multiple IP 
addresses to communicate with multiple Ethernet/IP devices, one per IP address.
The client bind IP address is specified when setting up the `SessionInfo` object. 
If not client IP address is specified then `INADDR_ANY` is requested in the `bind`
call.

To use this library with multiple devices on a machine, do the following.

1. Run the `add_ip` script, specifying the base and range of IP addresses to create.
For example, run

```sh
sudo add_ip 10.140.131.0 1 3
```
to create local IP addresses 10.140.131.1, 10.140.131.2, and 10.140.131.3.

2. When setting up the `SessionInfo` for each device, use one of these IP 
addresses. Your code should look like the following.

```c++
    session_info = std::make_shared<SessionInfo>(host, port, std::chrono::milliseconds(1000), client); 
```
where `host` is the IP address of the host/target device, `port` is the port (44818 or 2222), and `client`
is the IP address to bind on the local machine.

3. When done, the extra IP addresses can be removed with the `remove_ip` script.
This script takes the same arguments as the original `add_ip` script.

To check the IP addresses that are set up for a given interface you can use the following command.

```
ip address show dev enp5s0
```
where `enp5s0` should be replaced with the name of your interface.

## Contribution

We welcome outside contributions for any improvements, features, or new devices (see below) to the library. Please create a pull request with unit/mock tests

## Vendor specific objects & devices

Our goal is to maintain an active device catalog of all EtherNet/IP devices and their objects that we encounter. We encourage others to contribute to this communal device catalog in /src/vendor/.

All vendor source files are automatically enabled. If you'd like to disable vendor files, you can disable with any of the below options.
1) set this option in CMakeLists.txt
```cmake
option(ENABLE_VENDOR_SRC "Enable vendor source" OFF)
```
2) set the cmake build flag 
```shell
-DENABLE_VENDOR_SRC=OFF
```
3) manually comment needed files in src/vendor/CMakeLists.txt

## Authors

Aleksey Timin

Adam Roth

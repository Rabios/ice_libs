#!/usr/bin/env bash

# Update packages, Then install required packages and toolchains to build ice_libs
sudo apt-get update -y
sudo apt-get install -y libc6-dev-i386 mingw-w64

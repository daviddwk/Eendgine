#!/bin/bash

g++ -std=c++17 -o game.out -lSDL2 -I include/ ./*.cpp ./glad/* ./eendgine/* ./stb/*

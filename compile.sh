#!/bin/bash

g++ -Wall -std=c++17 -o game.out -lSDL2 -lassimp -I include/ ./*.cpp ./glad/* ./eendgine/* ./stb/*

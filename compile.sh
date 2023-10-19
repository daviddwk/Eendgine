#!/bin/bash

g++ -std=c++17 -o game.out -lSDL2 -lassimp -I include/ ./*.cpp ./glad/* ./eendgine/* ./stb/*

#!/usr/bin/bash

set -xe

cc -Wall -Wextra -Wpedantic -o app main.c

time ./app

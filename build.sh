#!/usr/bin/bash

set -xe

cc -Wall -Wextra -pedantic -o app linked_list.c

time ./app

#!/bin/bash
make clean && make -C ../ clean && make -C ../ -j12 && make -j12 && ./bin/tests

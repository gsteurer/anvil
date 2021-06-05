#!/bin/bash
make clean && make -C ../anvil/ clean && make -C ../anvil/ -j12 && make -j12 && ./bin/tests

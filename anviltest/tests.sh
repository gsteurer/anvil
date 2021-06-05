#!/bin/bash
make clean && make -C ../anvil/ clean && make -C ../anvil/ && make && ./bin/tests

#!/bin/bash
mkdir dir15_1 dir15_2

touch dir15_1/foo dir15_1/bar
touch dir15_2/foo dir15_2/bar dir15_2/baz
cp -u -p dir15_2/* dir15_1/
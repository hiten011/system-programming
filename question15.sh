#!/bin/bash
mkdir dir15 dir15_2

touch dir15/foo dir15/bar
touch dir15_2/foo dir15_2/bar dir15_2/baz
cp -u -p dir15_2/* dir15/
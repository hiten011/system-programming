#!/bin/bash
input="$1";
ls -lat | tail +2 | head -"$input"
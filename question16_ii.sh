#!/bin/bash

# copying directory
cp -r dir16_1 dir16_1_copy

mv dir16_1/dir16_2/dir16_3/dir16_4 dir16_1/dir16_2/
mv dir16_1/dir16_2/file16_2 dir16_1/dir16_2/file16_2_renamed
rm dir16_1/dir16_5/file16_4

rm -r dir16_1_copy/dir16_5
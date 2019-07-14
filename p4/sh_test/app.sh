#!/usr/bin/env bash
# usage ./app [username] [execute program] [human vs human input dir] [human myOpic input dir]
# EFFECT: generate a dir username_result, with test output inside.
result=$1_result
rm -r ${result}
mkdir ${result}
cd ${result}
for file in $(ls ../$3); do
    to_save="${file}_hh_res"
    ../$2 h h <../$3/${file} >${to_save}
done

for file in $(ls ../$4); do
    to_save="${file}_hm_res"
    ../$2 h m ${file} <../$4/${file} >${to_save}
done

int=-114514

while (($int <= 114514)); do
    to_save="${int}_mm_res"
    ../$2 m m $int >${to_save}
    add=500
    int=$(expr $int + $add)
done

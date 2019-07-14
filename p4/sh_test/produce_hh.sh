seedone=12
seedtwo=9543
cd hh
while (($seedone <= 988)); do

    touch ${seedone}vs${seedtwo}
    ../generate $seedone $seedtwo >${seedone}vs${seedtwo}

    seedone=$(expr $seedone + 13)
    seedtwo=$(expr $seedtwo + 17)
done

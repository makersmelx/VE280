#usage: ./diff.sh [use1] [user2]
#REQUIRE: app.sh already done
#OUTPUT: Nothing if one file is the same
#        diff -y in detail in dir "diff_detail" if there is file difference
rm -r diff_detail
mkdir diff_detail
for file in $(ls $1_result); do
    result=$(diff $1_result/${file} $2_result/${file} -q)
    if [ "$result" = "Files $1_result/$file and $2_result/${file} differ" ]; then
        echo $result
        cd diff_detail
        diff ../$1_result/${file} ../$2_result/${file} -y >${file}
        cd ../
    fi
done

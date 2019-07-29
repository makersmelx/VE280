# Usage:
#       ./app.sh gcall <range_start> <add each time ><range_end> generate cases
#       ./app.sh c  clear all the cases and diff_detail file
#       ./app.sh r <name> <executable call dir> <executable calc dir>
#       ./app.sh d <name2> <name3>
#       ./app.sh gcalc <num of expressions> <RPN cpp source> <expression raw> 

if [ "$1" = "h" ]; then
    echo "Help:
    Generate call cases
        ./app.sh gcall <range_start> <add each time> <range_end> 

    Generate calc cases  
        ./app.sh gcalc <num of expressions> <RPN cpp source> <expression raw>
    
    Clear all the compare files
        ./app.sh c  
    
    Run and set results
        ./app.sh r <name> <executable call dir> <executable calc dir>

    Run and set calc results only
        ./app.sh rcalc <name> <executable call dir> <executable calc dir>

    Run and set call results only
        ./app.sh rcall <name> <executable call dir> <executable calc dir>

    Compare two users' results
        ./app.sh d <name2> <name3>"
fi

if [ "$1" = "c" ]; then
    rm -r cases
    rm -r *_result
    rm -r diff_detail*
    rm -r calc_*
fi

if [ "$1" = "gcall" ]; then
    g++ -o generate rand_output.cpp
    mkdir call_cases
    cd call_cases
    int=$2
    while (($int <= $3)); do
        to_save="${int}"
        ../generate $int >$to_save
        add=$4
        int=$(expr $int + $add)
    done
    cd ../
    rm -f generate
fi

if [ "$1" = "rcall" ]; then
    dir="$2_result"
    mkdir $dir
    cd $dir
    for file in $(ls ../call_cases); do
        to_save="${file}_call"
        ../$3 <../call_cases/$file >$to_save
    done
fi

if [ "$1" = "rcalc" ]; then
    dir="$2_result"
    mkdir $dir
    cd $dir
    for file in $(ls ../calc_in); do
        to_save="${file}_calc"
        ../$4 <../calc_in/$file >$to_save
    done
fi

if [ "$1" = "r" ]; then
    dir="$2_result"
    mkdir $dir
    cd $dir
    for file in $(ls ../call_cases); do
        to_save="${file}_call"
        ../$3 <../call_cases/$file >$to_save
    done
    for file in $(ls ../calc_in); do
        to_save="${file}_calc"
        ../$4 <../calc_in/$file >$to_save
    done
fi

if [ "$1" = "gcalc" ]; then
    g++ -o generate $3
    mkdir calc_in
    mkdir calc_stdOut
    cd calc_in
    int=0
    while ((int < $2)); do
        touch "$int"
        add=1
        int=$(expr $int + $add)
    done
    cd ../calc_stdOut
    for file in $(ls ../calc_in); do
        touch "stdAns_$file"
    done
    cd ../
    ./generate calc_in calc_stdOut <$4
    rm -f generate
fi

if [ "$1" = "d" ]; then
    rm -r diff_detail
    mkdir diff_detail
    echo "Calc: $2 result comparison with standard begin!"
    for file in $(ls calc_in);do
        result=$(diff $2_result/${file}_calc calc_stdOut/stdAns_${file} -q)
        if [ "$result" = "Files $2_result/${file}_calc and calc_stdOut/stdAns_${file} differ" ]; then
            echo $result
            cd diff_detail
            diff ../$2_result/${file}_calc ../calc_stdOut/stdAns_${file} -y >"$2_${file}"
            cd ../
        fi
    done
    echo "Calc: $3 result comparison with standard begin!"
    for file in $(ls calc_in);do
        result=$(diff $3_result/${file}_calc calc_stdOut/stdAns_${file} -q)
        if [ "$result" = "Files $3_result/${file}_calc and calc_stdOut/stdAns_${file} differ" ]; then
            echo $result
            cd diff_detail
            diff ../$3_result/${file}_calc ../calc_stdOut/stdAns_${file} -y >"$3_${file}"
            cd ../
        fi
    done
    echo "Call: $2 and $3 result comparison begin!"
    cd $2_result
    for file in *call;do
        result=$(diff ${file} ../$3_result/${file} -q)
        
        if [ "$result" = "Files $file and ../$3_result/${file} differ" ]; then
            echo $result
            cd ../diff_detail
            diff ../$2_result/${file} ../$3_result/${file} -y >${file}
            cd ../$2_result
        fi
    done
    

fi


if [ "$1" = "test" ]; then
    for file in calc_stdOut/std*;do
        echo $file
    done

fi
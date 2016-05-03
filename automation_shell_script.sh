for ((i=7; i<14; i++)); do

    if ((i==0)); then
        weath='0'
    fi
    if ((i==1)); then
        weath='1e-10'
    fi
    if ((i==2)); then
        weath='1e-8'
    fi
    if ((i==3)); then
        weath='1e-6'
    fi
    if ((i==4)); then
        weath='3e-6'
    fi
    if ((i==5)); then
        weath='6e-6'
    fi
    if ((i==6)); then
        weath='1e-5'
    fi
    if ((i==7)); then
        weath='3e-5'
    fi
    if ((i==8)); then
        weath='6e-5'
    fi
    if ((i==9)); then
        weath='1e-4'
    fi
    if ((i==10)); then
        weath='3e-4'
    fi
    if ((i==11)); then
        weath='6e-4'
    fi
    if ((i==12)); then
        weath='1e-3'
    fi
    if ((i==13)); then
        weath='3e-3'
    fi

    echo $weath


    sed -i '' '27s@.*@parameters[0].max_weath='$weath'; //This is the maximum weathering rate@' inout.c
    echo $weath

    make
    ./jb split10_hi_$weath
done

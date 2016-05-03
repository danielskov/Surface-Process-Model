cd output
find . -name "output*" -type f -print0 |xargs -0 stat -f "%m %N" | sort -rn | head -1 | cut -f2- -d" " > last_file
head -c 65536K $1 | strings | grep -E "^<[0-9]+>\[ *[0-9\.]+\]" > $2

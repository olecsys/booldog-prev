#!/bin/bash
old_dir="`pwd`/`basename "$0"`"
old_dir=`dirname "$old_dir"`
cd "`dirname "$0"`"
script_dir="`pwd`/`basename "$0"`"
script_dir=`dirname "$script_dir"`
cd "$old_dir"

path_to_copy=$script_dir/../core/inc/booldog
if [ ! -d "$path_to_copy" ]; then
	mkdir -p "$path_to_copy"
fi
cp -f "$script_dir/include/"* "$path_to_copy/"
find "$path_to_copy/" -name "*.svn" -exec rm -rf {} \;

echo "Copy files to $path_to_copy success"

path_to_copy=$script_dir/../rux/extern_includes/booldog
if [ ! -d "$path_to_copy" ]; then
	mkdir -p "$path_to_copy"
fi
cp -f "$script_dir/include/"* "$path_to_copy/"
find "$path_to_copy/" -name "*.svn" -exec rm -rf {} \;

echo "Copy files to $path_to_copy success"

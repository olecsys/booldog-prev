#!/bin/bash
old_dir="`pwd`/`basename "$0"`"
old_dir=`dirname "$old_dir"`
cd "`dirname "$0"`"
script_dir="`pwd`/`basename "$0"`"
script_dir=`dirname "$script_dir"`

os=linux
platform=x64
project_name=booldog.test.exe

rebuild_success="true"


configure_path=$script_dir/../tools/rux.configure/$os/$platform/rux.configure
if [ ! -e "$configure_path" ]
then
	configure_path=$script_dir/../../tools/rux.configure/$os/$platform/rux.configure
fi
if [ $rebuild_success = "true" ]
then	
	rebuild_success="false"
	chmod +x "$configure_path" && rebuild_success="true"
fi

if [ $rebuild_success = "true" ]
then	
	rebuild_success="false"
	"$configure_path" --generate-makefile "$script_dir/test.ruxprj" && rebuild_success="true"
fi

if [ $rebuild_success = "true" ]
then	
	rebuild_success="false"
	cd "$script_dir/../projects/$os/$platform/$project_name" && rebuild_success="true"
fi

make -j 4 -f "$script_dir/../projects/$os/$platform/$project_name/Makefile" clean && rebuild_success="true"

if [ $rebuild_success = "true" ]
then	
	rebuild_success="false"
	make -j 4 -f "$script_dir/../projects/$os/$platform/$project_name/Makefile" && rebuild_success="true"
fi

if [ $rebuild_success = "true" ]
then	
	rebuild_success="false"
	make -j 4 -f "$script_dir/../projects/$os/$platform/$project_name/Makefile" PostBuild && rebuild_success="true"
fi

red='\e[0;31m'
green='\e[0;32m'
nocolor='\e[0m'
if [ $rebuild_success = "true" ]
then
	echo -e "${green}rux project building succeeded.Press <ENTER> to continue${nocolor}"
	cd "$old_dir"
	exit 0
else
	echo -e "${red}rux project building failed.Press <ENTER> to continue${nocolor}"
	cd "$old_dir"
	exit 1
fi


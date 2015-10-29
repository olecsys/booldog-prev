#!/bin/bash
old_dir="`pwd`/`basename "$0"`"
old_dir=`dirname "$old_dir"`
cd "`dirname "$0"`"
script_dir="`pwd`/`basename "$0"`"
script_dir=`dirname "$script_dir"`

os=linux
platform=x64
rebuild_success="true"

if [ $rebuild_success = "true" ]
then	
	rebuild_success="false"
	"$script_dir/../../tools/rux.configure/$os/$platform/rux.configure" --rebuild-project "$script_dir/test.ruxprj" --configuration "$os $platform" && rebuild_success="true"
fi
red='\e[0;31m'
green='\e[0;32m'
nocolor='\e[0m'
if [ $rebuild_success = "true" ]
then
	echo -e "${green}rux project building succeeded.Press <ENTER> to continue${nocolor}"
else
	echo -e "${red}rux project building failed.Press <ENTER> to continue${nocolor}"
fi
cd "$old_dir"
read

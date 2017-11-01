#!/bin/sh
if [ -z "$1" ]; then
	echo "No branch name supplied" ;
else
	git checkout -b $1; git push --set-upstream origin $1 ;
fi

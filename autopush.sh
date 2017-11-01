#!/bin/sh

echo "Performing Autopush!";
git status;

if [[ $1 = "-m" ]]; then
	git add .; 
	git commit -m "autopushed: $2"; 
	git status; git push;
else
	git add .; 
	git commit -m "autopushed with no message"; 
	git status; 
	git push;
fi

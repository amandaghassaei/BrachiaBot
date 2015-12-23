#!/bin/sh

cd ~/Research/CBAStuff/git/uls
git co master
git fetch upstream
git merge upstream/master
git push origin master
cd ~/Research/CBAStuff/git/archives/dma
git fetch origin
git merge origin/master
git subtree pull -P Web/uls fabpeople:people/amanda.ghassaei/uls master --squash
git push origin master

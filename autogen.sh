#!/bin/sh
rm -f config.cache
autoheader
#aclocal 
autoconf
automake -a --add-missing
exit

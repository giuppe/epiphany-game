#!/bin/sh
rm -f config.cache
aclocal 
autoheader
autoconf
automake -a --add-missing
exit

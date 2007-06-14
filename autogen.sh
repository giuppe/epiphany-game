#!/bin/sh
rm -f config.cache
aclocal -I aclocal
autoheader
autoconf
automake -a --add-missing
exit

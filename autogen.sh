#!/bin/sh
rm -f config.cache
autoheader
aclocal
echo "AC_DEFUN(EPIPHANY_EXPAND_DIR, [" >>aclocal.m4
echo "\$1=\$2" >>aclocal.m4
echo "\$1=\`(" >>aclocal.m4
echo "test \"x\$prefix\" = xNONE && prefix=\"\$ac_default_prefix\"" >>aclocal.m4
echo "test \"x\$exec_prefix\" = xNONE && exec_prefix=\"\${prefix}\"" >>aclocal.m4
echo "eval echo \\\"\"[\$]\$1\"\\\"" >>aclocal.m4
echo ")\`" >>aclocal.m4
echo "])" >>aclocal.m4
 autoconf
automake -a --add-missing
exit

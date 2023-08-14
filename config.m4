PHP_ARG_ENABLE(deep_client_php_extension, whether to enable PHP Python Extension support,
[  --enable-deep_client_php_extension          Enable PHP Python Extension support])

if test $DEEP_CLIENT_PHP_EXTENSION != "no"; then
  PHP_SUBST(DEEP_CLIENT_PHP_EXTENSION_SHARED_LIBADD)
  PHP_NEW_EXTENSION(deep_client_php_extension, deep_client_php_extension.c, $ext_shared)
fi

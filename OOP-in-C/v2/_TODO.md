== More TBD ==
Tests have been rewritten to use WOGTEST. This required to add
more files. Furthermore the `main` program was moved to a separate
compilation unit (`app_main.c`) to support the idea of "separation
of concerns". The function `run_app` called from `main` is
introduced via an `extern` declaration.

#include <stdio.h>
#include <stdlib.h>
#include <janet/janet.h>

static int running = 1;

static Janet quit(int32_t argc, Janet *argv)
{
    running = 0;
    return janet_wrap_nil();
}

static int read_a_line(char **lp,
                       size_t *n,
                       FILE *fp,
                       ssize_t *read)
{
    int rc;
    if(!running) return 0;
    rc = (*read = getline(lp, n, fp));
    return (rc != -1);
}

int main(int argc, char **argv) {
    JanetTable *env;
    FILE *fp;
    char *line;
    size_t len;
    ssize_t read;

    line = NULL;

    fp = stdin;

    janet_init();

    env = janet_core_env(NULL);
    janet_def(env, "quit", janet_wrap_cfunction(quit), NULL);

    len = 0;
    while(read_a_line(&line, &len, fp, &read)) {
        janet_dostring(env, line, NULL, NULL);
    }

    janet_deinit();

    return 0;
}

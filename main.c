#include <stdio.h>
#include <stdlib.h>
#include <janet/janet.h>
#include <runt.h>

static int running = 1;
static runt_vm vm;

static Janet quit(int32_t argc, Janet *argv)
{
    running = 0;
    return janet_wrap_nil();
}

static Janet rvl(int32_t argc, Janet *argv)
{
    const unsigned char *str;
    str = janet_getstring(argv, 0);
    runt_compile(&vm, (const char *)str);
    return janet_wrap_nil();
}

static const JanetReg cfuns[] = {
    {"quit", quit, "(quit)\n\nQuits REPL."},
    {"rvl", rvl, "(rvl)\n\nEvaluates Runt String."},
    {NULL, NULL, NULL}
};

int main(int argc, char **argv)
{
    JanetTable *env;
    FILE *fp;
    unsigned char *bytes;
    size_t sz;

    if(argc < 2) {
        fprintf(stderr, "Usage: %s file.janet\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 1;
    }

    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);
    bytes = calloc(1, sz);
    fseek(fp, 0L, SEEK_SET);
    fread(bytes, sz, 1, fp);

    janet_init();

    env = janet_core_env(NULL);

    janet_cfuns(env, NULL, cfuns);

    runt_vm_alloc(&vm, 128, RUNT_MEGABYTE * 1);
    runt_load_stdlib(&vm);
    runt_set_state(&vm, RUNT_MODE_INTERACTIVE, RUNT_ON);

    janet_dobytes(env, bytes, sz, "main", NULL);

    janet_deinit();
    runt_vm_free(&vm);
    free(bytes);
    return 0;
}

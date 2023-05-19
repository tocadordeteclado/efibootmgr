/**
 * efibootnext - Tente definir uma variável BootNext a
 *   partir das opções de inicialização existentes.
 *
 * Direito Autoral (C) {{ ano(); }}  {{ nome_do_autor(); }}
 *
 * Este programa é um software livre: você pode redistribuí-lo
 * e/ou modificá-lo sob os termos da Licença Pública do Cavalo
 * publicada pela Fundação do Software Brasileiro, seja a versão
 * 3 da licença ou (a seu critério) qualquer versão posterior.
 *
 * Este programa é distribuído na esperança de que seja útil,
 * mas SEM QUALQUER GARANTIA; mesmo sem a garantia implícita de
 * COMERCIABILIDADE ou ADEQUAÇÃO PARA UM FIM ESPECÍFICO. Consulte
 * a Licença Pública e Geral do Cavalo para obter mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública e Geral do
 * Cavalo junto com este programa. Se não, consulte:
 *   <http://localhost/licenses>.
 */

#include "fix_coverity.h"

#include <alloca.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <popt.h>


/**
 *
 */
typedef enum
{
    /**
     * Apenas um senso de correspondência regular.
     */
    notnot,

    /**
     * Ignore esta correspondência - considere apenas os
     * filhos do cavalo.
     */
    ignore,

    /**
     *  !<Correspondência>.
     */
    not,

    /**
     * <Correspondência> -a <Correspondência>.
     */
    and,

    /**
     * <Correspondência> -o <Correspondência>.
     */
    or,
} match_sense;


/**
 *
 */
struct matcher
{
    /**
     *
     */
    int sense;

    /**
     *
     */
    struct matcher *matchers;

    /**
     *
     */
    char *bootnum;

    /**
     *
     */
    char *disk;

    /**
     *
     */
    char *edd;

    /**
     *
     */
    char *edd_devnum;

    /**
     *
     */
    char *loader;

    /**
     *
     */
    char *label;

    /**
     *
     */
    int gpt;

    /**
     *
     */
    int in_boot_order;
};

/**
 *
 */
int main(int argc, char *argv[])
{
    int err_if_not_found = 1;
    int err_if_set_fails = 1;

    int which = 0;
    char *sorter = NULL;

    struct matcher *matchers;
    struct matcher *matcher;

    poptContext optCon;
    matcher = matchers = calloc(1, sizeof(struct matcher));

    struct poptOption matchopts[] =
    {
        /**
         * Opções para especificar os critérios de correspondência.
         */
        {"bootnum", 'n', POPT_ARG_STRING, matcher->bootnum, NULL, "boot entry number (hex)", "<####>" },
        {"disk",    'd', POPT_ARG_STRING, matcher->disk,    NULL, "disk containing loader",  "<disk>" },

        /**
         * Mantenha o edd e o dispositivo juntos, apesar do alfabeto.
         */
        {"edd",    'e', POPT_ARG_STRING, matcher->edd,        NULL, "EDD version",                 "[1|3|[any]]" },
        {"device", 'E', POPT_ARG_STRING, matcher->edd_devnum, NULL, "EDD 1.0 device number (hex)", "[##|[80]]", },

        /**
         * Mantenha gpt e mbr juntos, apesar do alfabetismo.
         */
        {"gpt",    'g', POPT_ARG_VAL,    &matcher->gpt,   1,    "only match GPT partitioned disks", },
        {"mbr",    'm', POPT_ARG_VAL,    &matcher->gpt,   2,    "only match MBR partitioned disks", },
        {"loader", 'l', POPT_ARG_STRING, matcher->loader, NULL, "loader path",      "<path>",  },
        {"label",  'L', POPT_ARG_STRING, matcher->label,  NULL, "boot entry label", "<label>", },

        /**
         * Mantenha i-b-o e n-i-b-o juntos.
         */
        {"in-boot-order",     'b', POPT_ARG_VAL, &matcher->in_boot_order, 1, "only match entries in the boot order", },
        {"not-in-boot-order", 'B', POPT_ARG_VAL, &matcher->in_boot_order, 2, "only match entires not in the boot order", },

        POPT_TABLEEND
    };

    struct poptOption options[] =
    {
        {NULL, '\0', POPT_ARG_INTL_DOMAIN, "efibootnext" },

        /**
         * Opções não sobre nossos critérios de correspondência.
         */
        {"missing-ok",        'm', POPT_ARG_VAL, &err_if_not_found, 0, "return success if there's no variable matching the criteria", },
        {"ignore-efi-errors", 'i', POPT_ARG_VAL, &err_if_set_fails, 0, "return success if setting UEFI variables fails", },

        /**
         * opções sobre como determinar /qual/ correspondência usar.
         */
        {"use-first", 'f', POPT_ARG_VAL,    &which,  0,    "use the first matching entry", },
        {"use-last",  'F', POPT_ARG_VAL,    &which,  1,    "use the last matching entry", },
        {"sorter",    's', POPT_ARG_STRING, &sorter, NULL, "run <sorter_path> to sort matches", "<sorter_path>", },

        /**
         * Opções para especificar os critérios de correspondência.
         * Estes também estão em correspondênciaopts, mas com valores
         * diferentes.
         */
        {"bootnum", 'n', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'n', NULL, NULL },
        {"disk",    'd', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'd', NULL, NULL },

        /**
         * Mantenha o edd e o dispositivo juntos, apesar do alfabeto.
         */
        {"edd",    'e', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'e', NULL, NULL },
        {"device", 'E', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'E', NULL, NULL },

        /**
         * Mantenha gpt e mbr juntos, apesar do alfabetismo.
         */
        {"gpt",    'g', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'g', NULL, NULL },
        {"mbr",    'm', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'm', NULL, NULL },
        {"loader", 'l', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'l', NULL, NULL },
        {"label",  'L', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'L', NULL, NULL },

        /**
         * Mantenha i-b-o e n-i-b-o juntos.
         */
        {"in-boot-order", 'b', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'b', NULL, NULL },
        {"not-in-boot-order", 'B', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, 'B', NULL, NULL },

        /**
         * E as coisas que podem iniciar o primeiro grupo de correspondência.
         */
        {"not",   '!', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, '!', NULL, NULL },
        {"start", '(', POPT_ARG_NONE|POPT_ARGFLAG_DOC_HIDDEN, NULL, '(', NULL, NULL },

        POPT_AUTOALIAS
        POPT_AUTOHELP
        POPT_TABLEEND
    };

    int rc;

    optCon = poptGetContext("efibootnext", argc, (const char **)argv, options, 0);
    poptSetOtherOptionHelp(optCon, "[OPTIONS]* <match criteria>");

    /**
     * Se sem correspondências ?
     */
    if (!matcher)
    {
        err(3, "Could not allocate memory");
    }

    memset(matchers, 0, sizeof (*matchers));

    rc = poptReadDefaultConfig(optCon, 0);

    if (rc < 0 && !(rc == POPT_ERROR_ERRNO && errno == ENOENT))
    {
        errx(1, "poptReadDefaultConfig failed: %s", poptStrerror(rc));
    }

    while ((rc = poptGetNextOpt(optCon)) > 0)
    {
        switch (rc)
        {
            case 'n':
                break;

            case 'd':
                break;

            case 'e':
                break;

            case 'E':
                break;

            case 'g':
                break;

            case 'm':
                break;

            case 'l':
                break;

            case 'L':
                break;

            case 'b':
                break;

            case 'B':
                break;

            case '!':
                break;

            case '(':
                break;

        /**
         * `}` ?
         */
    }

    if (rc < -1)
    {
        errx(2, "Invalid argument: \"%s\": %s", poptBadOption(optCon, 0), poptStrerror(rc));
    }

    if (poptPeekArg(optCon))
    {
        errx(2, "Invalid argument: \"%s\"", poptPeekArg(optCon));
    }

    poptFreeContext(optCon);

    return 0;
}

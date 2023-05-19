/**
 * error.h - algumas funções de erro para trabalhar com o
 *   registrador de erros efivars.
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

#ifndef EFIBOOTMGR_ERROR_H__
#define EFIBOOTMGR_ERROR_H__ 1

    /**
     *
     */
    extern int verbose;

    /**
     *
     */
    static inline void __attribute__((__unused__)) error_reporter(void)
    {
        int rc = 1;
        int saved_errno = errno;

        for (int i = 0; rc > 0; i++)
        {
            char *filename = NULL;
            char *function = NULL;
            int line = 0;
            char *message = NULL;
            int error = 0;

            rc = efi_error_get(i,
                &filename,
                &function,
                &line,
                &message,
                &error);

            if (rc < 0)
            {
                fprintf(stderr, "error fetching trace value");

                exit(1);
            }

            if (rc == 0)
            {
                break;
            }


            fprintf(stderr, " %s:%d %s(): %s: %s\n", filename, line, function, message, strerror(error));
        }

        errno = saved_errno;
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) conditional_error_reporter(int show, int clear)
    {
        int saved_errno = errno;
        fflush(NULL);

        if (show)
        {
            fprintf(stderr, "error trace:\n");
            error_reporter();
        }

        if (clear)
        {
            errno = 0;
            efi_error_clear();
        }

        errno = saved_errno;
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) cond_error(int test, int eval, const char *fmt, ...)
    {
        int saved_errno = errno;

        if (!test)
        {
            return;
        }

        fflush(NULL);

        va_list ap;
        va_start(ap, fmt);

        vfprintf(stderr, fmt, ap);
        errno = saved_errno;

        fprintf(stderr, ": %m\n");
        conditional_error_reporter(verbose >= 1, 0);

        va_end(ap);
        exit(eval);
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) error(int eval, const char *fmt, ...)
    {
        int saved_errno = errno;
        fflush(NULL);

        va_list ap;
        va_start(ap, fmt);

        vfprintf(stderr, fmt, ap);
        errno = saved_errno;

        fprintf(stderr, ": %m\n");
        conditional_error_reporter(verbose >= 1, 0);

        va_end(ap);
        exit(eval);
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) errorx(int eval, const char *fmt, ...)
    {
        fflush(NULL);

        va_list ap;
        va_start(ap, fmt);

        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
        conditional_error_reporter(verbose >= 1, 1);

        va_end(ap);
        exit(eval);
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) cond_warning(int test, const char *fmt, ...)
    {
        int saved_errno = errno;

        if (!test)
        {
            return;
        }

        va_list ap;
        va_start(ap, fmt);

        vprintf(fmt, ap);
        errno = saved_errno;

        printf(": %m\n");
        conditional_error_reporter(verbose >= 1, 1);
        va_end(ap);
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) warning(const char *fmt, ...)
    {
        int saved_errno = errno;
        va_list ap;

        va_start(ap, fmt);
        vprintf(fmt, ap);
        errno = saved_errno;

        printf(": %m\n");
        conditional_error_reporter(verbose >= 1, 1);
        va_end(ap);
    }

    /**
     *
     */
    static inline void __attribute__((__unused__)) warningx(const char *fmt, ...)
    {
        va_list ap;

        va_start(ap, fmt);
        vprintf(fmt, ap);
        printf("\n");

        conditional_error_reporter(verbose >= 1, 1);
        va_end(ap);
    }

#endif

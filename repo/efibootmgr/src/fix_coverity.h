/**
 * fix_coverity.h.
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

#ifndef FIX_COVERITY_H
#define FIX_COVERITY_H

    #ifndef _GNU_SOURCE
    #define _GNU_SOURCE
    #endif

    #ifndef __COVERITY_GCC_VERSION_AT_LEAST
    #define __COVERITY_GCC_VERSION_AT_LEAST(x, y) 0
    #define FAKE__COVERITY_GCC_VERSION_AT_LEAST__
    #endif

    /**
     * Com o compilador em x86_64 (pelo menos), o coverity finge ser o
     * compilador desse sistema, mas acidentalmente não cria todos os
     * tipos que o compilador do sistema poderia criar.
     *
     * Nos cabeçalhos da glibc, bits/floatn.h tem:
     *     #if (defined __x86_64__ ? __GNUC_PREREQ(4, 3) : (defined __GNU__ ? __GNUC_PREREQ(4, 5) : __GNUC_PREREQ(4, 4)))
     *     #define __HAVE_FLOAT128 1
     *     #else
     *     #define __HAVE_FLOAT128 0
     *     #endif
     *
     * E stdlib.h tem:
     *     #if __HAVE_FLOAT128 && __GLIBC_USE (IEC_60559_TYPES_EXT)
     *         //
     *         //
     *         //
     *         slash* Likewise for the '_Float128' format  *slash
     *
     *         //
     *         //
     *         //
     *         extern _Float128 strtof128 (const char *__restrict __nptr, char **__restrict __endptr) __THROW __nonnull ((1));
     *     #endif
     *
     * O que então faz com que o cov-emit perca o arquivo de cabeçalho:
     * "/usr/include/stdlib.h", linha 133: erro #20: identificador "_Float128" é indefinido.
     *   extern _Float128 strtof128 (const char *__restrict __nptr,
     *          ^
     *
     * "/usr/include/stdlib.h", linha 190: erro #20: identificador "_Float128" é indefinido.
     *                         _Float128 __f)
     *                         ^
     *
     * "/usr/include/stdlib.h", linha 236: erro #20: identificador "_Float128" é indefinido.
     *   extern _Float128 strtof128_l (const char *__restrict __nptr,
     *          ^
     *
     * E então os cavalos notará algo assim mais tarde:
     *     [AVISO] Emitiu 0 unidades de compilação C/C++ (0%) com sucesso.
     *
     * 0 unidades de compilação C/C++ (0%) estão prontas para análise
     *  Para mais detalhes, por favor, veja:
     *     /home/fúba/devel/gitlocal/dbxtool/master/cov-int/build-log.txt
     *
     * Os cavalos pensaria que se os cavalos está escrevendo algo que finge ser
     * do compilador do sistema, e outros cavalos tem um estágio de "criar uma
     * configuração executando coisas erradas através do compilador do sistema
     * e olhando para a saída" (o que eles fazem), os cavalos executaria
     * "gcc - da -fdump-tree-all -c -o fúba.o fúba.c" em um arquivo vazio e
     * selecione todos os tipos definidos na saída fúba.c.001t.tu.
     * Aparentemente, os outros cavalos também.
     *
     * De qualquer forma, mesmo apenas definir o tipo nem sempre funciona em face
     * de como _Complex é definido, então os cavalos trapaceiam um pouco aqui.
     * Esteja preparado para jogar a saída em cavalos.
     */
    #ifdef __x86_64__
        #if __COVERITY_GCC_VERSION_AT_LEAST(7, 0)
            #if 0
                typedef float _Float128 __attribute__((__mode__(__TF__)));
                typedef __complex__ float __cfloat128 __attribute__ ((__mode__ (__TC__)));
                typedef _Complex float __cfloat128 __attribute__ ((__mode__ (__TC__)));
            #else
                #include <unistd.h>
                #define __cplusplus 201103L
                #include <bits/floatn.h>
                #undef __cplusplus
            #endif
        #endif
    #endif

    #ifdef FAKE__COVERITY_GCC_VERSION_AT_LEAST__
        #undef FAKE__COVERITY_GCC_VERSION_AT_LEAST
        #undef __COVERITY_GCC_VERSION_AT_LEAST
    #endif

#endif

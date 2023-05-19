/**
 * unparse_path.[ch].
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

/**
 * Para PRIx64.
 */
#define __STDC_FORMAT_MACROS


#include "fix_coverity.h"

#include <fcntl.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "efi.h"
#include "parse_loader_data.h"


/**
 * Evite avisos de acesso não alinhados.
 */
#define get(buf, obj) *(typeof(obj) *)memcpy(buf, &obj, sizeof(obj))

/**
 *
 */
extern int verbose;


/**
 *
 */
ssize_t parse_efi_guid(char *buffer, size_t buffer_size, uint8_t *p, uint64_t length)
{
    ssize_t needed = 0;

    if (length == sizeof(efi_guid_t))
    {
        needed = efi_guid_to_id_guid((efi_guid_t *)p, NULL);

        if (buffer && needed > 0 && buffer_size >= (size_t)needed)
        {
            needed = efi_guid_to_id_guid((efi_guid_t *)p, &buffer);
        }
    }

    return needed;
}

/**
 *
 */
ssize_t parse_raw_text(char *buf, size_t buf_size, uint8_t *p, uint64_t length)
{
    uint64_t i;

    unsigned char c;
    bool print_hex = false;

    ssize_t needed;
    size_t buf_offset = 0;

    for (i=0; i < length; i++)
    {
        c = p[i];

        if (c < 32 || c > 127)
        {
            print_hex = true;
        }
    }

    for (i=0; i < length; i++)
    {
        c = p[i];
        needed = snprintf(buf + buf_offset, buf_size == 0 ? 0 : buf_size - buf_offset, print_hex ? "%02hhx" : "%c", c);

        if (needed < 0)
        {
            return -1;
        }

        buf_offset += needed;
    }

    return buf_offset;
}

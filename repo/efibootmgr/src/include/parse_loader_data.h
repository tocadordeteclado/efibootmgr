/**
 * parse_loader_data.h.
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

#ifndef _PARSE_LOADER_DATA_H
#define _PARSE_LOADER_DATA_H

    #include <stdint.h>
    #include "efi.h"


    /**
     *
     */
    ssize_t parse_efi_guid(char *buffer, size_t buffer_size, uint8_t *p, uint64_t length);

    /**
     *
     */
    ssize_t parse_raw_text(char *buffer, size_t buffer_size, uint8_t *p, uint64_t length);

#endif

/**
 * efi.[ch] - Definições de interface de firmware extensível.
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

#ifndef EFI_H
#define EFI_H

    /**
     * Interface de firmware extensível.
     * Baseado em 'Extensible Firmware Interface Specification'
     * versão 1.02, 12 Dezembro, 2000.
     */
    #include <stdint.h>
    #include <dirent.h>
    #include <efivar.h>


    /**
     * Atributos de opção de inicialização.
     */

    /**
     *
     */
    #define LOAD_OPTION_ACTIVE 0x00000001

    /**
     *
     */
    #define LOAD_OPTION_FORCE_RECONNECT 0x00000002

    /**
     *
     */
    #define LOAD_OPTION_HIDDEN 0x00000008

    /**
     *
     */
    #define LOAD_OPTION_CATEGORY_MASK 0x00001f00

    /**
     *
     */
    #define LOAD_OPTION_CATEGORY_BOOT 0x00000000

    /**
     *
     */
    #define LOAD_OPTION_CATEGORY_APP 0x00000100

    /**
     * GUIDs.
     */

    /**
     *
     */
    #define BLKX_UNKNOWN_GUID EFI_GUID(0x47c7b225, 0xc42a, 0x11d2, 0x8e57, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)

    /**
     *
     */
    #define ADDRESS_RANGE_MIRROR_VARIABLE_GUID EFI_GUID(0x7b9be2e0, 0xe28a, 0x4197, 0xad3e, 0x32, 0xf0, 0x62, 0xf9, 0x46, 0x2c)

    /**
     * Funções exportadas.
     */

    /**
     *
     */
    extern int read_boot_var_names(char ***namelist);

    /**
     *
     */
    extern int read_var_names(const char *prefix, char ***namelist);

    /**
     *
     */
    extern ssize_t make_linux_load_option(uint8_t **data, size_t *data_size, uint8_t *optional_data, size_t optional_data_size);

    /**
     *
     */
    extern ssize_t get_extra_args(uint8_t *data, ssize_t data_size);

    /**
     *
     */
    typedef struct
    {
        uint8_t mirror_version;
        uint8_t mirror_memory_below_4gb;
        uint16_t mirror_amount_above_4gb;
        uint8_t mirror_status;
    } __attribute__((packed)) ADDRESS_RANGE_MIRROR_VARIABLE_DATA;

    /**
     *
     */
    #define MIRROR_VERSION 1

    /**
     *
     */
    #define ADDRESS_RANGE_MIRROR_VARIABLE_CURRENT "MirrorCurrent"

    /**
     *
     */
    #define ADDRESS_RANGE_MIRROR_VARIABLE_REQUEST "MirrorRequest"

#endif

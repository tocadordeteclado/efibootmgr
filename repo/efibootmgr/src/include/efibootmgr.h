/**
 * efibootmgr.h - Manipula variáveis EFI conforme exportadas
 *   em /proc/efi/vars.
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

#ifndef _EFIBOOTMGR_H
#define _EFIBOOTMGR_H

    /**
     *
     */
    #define EFIBOOTMGR_IPV4 0

    /**
     *
     */
    #define EFIBOOTMGR_IPV6 1

    /**
     *
     */
    #define EFIBOOTMGR_IPV4_ORIGIN_DHCP 0

    /**
     *
     */
    #define EFIBOOTMGR_IPV4_ORIGIN_STATIC 1

    /**
     *
     */
    #define EFIBOOTMGR_IPV6_ORIGIN_STATIC 0

    /**
     *
     */
    #define EFIBOOTMGR_IPV6_ORIGIN_STATELESS 1

    /**
     *
     */
    #define EFIBOOTMGR_IPV6_ORIGIN_STATEFUL 2

    /**
     *
     */
    #define EFIBOOTMGR_PATH_ABBREV_UNSPECIFIED 0

    /**
     *
     */
    #define EFIBOOTMGR_PATH_ABBREV_EDD10 1

    /**
     *
     */
    #define EFIBOOTMGR_PATH_ABBREV_HD 2

    /**
     *
     */
    #define EFIBOOTMGR_PATH_ABBREV_NONE 3

    /**
     *
     */
    #define EFIBOOTMGR_PATH_ABBREV_FILE 4

    /**
     *
     */
    typedef enum
    {
        boot,
        driver,
        sysprep,
    } ebm_mode;

    /**
     *
     */
    typedef struct
    {
        /**
         *
         */
        int argc;

        /**
         *
         */
        char **argv;

        /**
         *
         */
        int optind;

        /**
         *
         */
        char *disk;

        /**
         *
         */
        int ip_version;

        /**
         *
         */
        char *iface;

        /**
         *
         */
        char *macaddr;

        /**
         *
         */
        char *local_ip_addr;

        /**
         *
         */
        char *remote_ip_addr;

        /**
         *
         */
        char *gateway_ip_addr;

        /**
         *
         */
        char *ip_netmask;

        /**
         *
         */
        uint16_t ip_local_port;

        /**
         *
         */
        uint16_t ip_remote_port;

        /**
         *
         */
        uint16_t ip_protocol;

        /**
         *
         */
        uint8_t ip_addr_origin;

        /**
         *
         */
        char *loader;

        /**
         *
         */
        unsigned char *label;

        /**
         *
         */
        char *order;

        /**
         *
         */
        int keep_old_entries;

        /**
         *
         */
        char *testfile;

        /**
         *
         */
        char *extra_opts_file;

        /**
         *
         */
        uint32_t part;

        /**
         *
         */
        int abbreviate_path;

        /**
         *
         */
        uint32_t edd10_devicenum;

        /**
         *
         */
        int num;

        /**
         *
         */
        int bootnext;

        /**
         *
         */
        int verbose;

        /**
         *
         */
        int active;

        /**
         *
         */
        int reconnect;

        /**
         *
         */
        int below4g;

        /**
         *
         */
        int above4g;

        /**
         *
         */
        int deduplicate;

        /**
         *
         */
        unsigned int delete:1;

        /**
         *
         */
        unsigned int delete_order:1;

        /**
         *
         */
        unsigned int delete_bootnext:1;

        /**
         *
         */
        unsigned int quiet:1;

        /**
         *
         */
        unsigned int showversion:1;

        /**
         *
         */
        unsigned int create:1;

        /**
         *
         */
        unsigned int unicode:1;

        /**
         *
         */
        unsigned int write_signature:1;

        /**
         *
         */
        unsigned int forcegpt:1;

        /**
         *
         */
        unsigned int set_timeout:1;

        /**
         *
         */
        unsigned int delete_timeout:1;

        /**
         *
         */
        unsigned int set_mirror_lo:1;

        /**
         *
         */
        unsigned int set_mirror_hi:1;

        /**
         *
         */
        unsigned int no_order:1;

        /**
         *
         */
        unsigned int driver:1;

        /**
         *
         */
        unsigned int sysprep:1;

        /**
         *
         */
        unsigned int explicit_label:1;

        /**
         *
         */
        short int timeout;

        /**
         *
         */
        uint16_t index;
    } efibootmgr_opt_t;

    /**
     *
     */
    extern efibootmgr_opt_t opts;

#endif

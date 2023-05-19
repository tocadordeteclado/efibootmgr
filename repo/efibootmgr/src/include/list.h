/**
 * list.h - Copiado do linux 2.4.4, em: linux/include/linux/list.h.
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

#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

    /**
     * Implementação simples de lista duplamente ligada.
     *
     * Algumas das funções internas ("__xxx") são úteis ao manipular
     * listas inteiras em vez de entradas únicas, já que às vezes já
     * conhecemos as entradas próximas/anteriores e podemos gerar um
     * código melhor usando-as diretamente em vez de usar as rotinas
     * genéricas de entrada única.
     */

    /**
     *
     */
    struct list_head
    {
        /**
         *
         */
        struct list_head *next, *prev;
    };

    /**
     *
     */
    typedef struct list_head list_t;

    /**
     *
     */
    #define LIST_HEAD_INIT(name) \
        { \
            &(name), \
            &(name) \
        }

    /**
     *
     */
    #define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

    /**
     *
     */
    #define INIT_LIST_HEAD(ptr) \
        do \
        { \
            (ptr)->next = (ptr); \
            (ptr)->prev = (ptr); \
        } while (0)

    /**
     * Insira uma nova entrada entre duas entradas consecutivas
     * conhecidas.
     *
     * Isso é apenas para manipulação de lista interna onde já
     * conhecemos as entradas anteriores/seguintes!
     */
    static __inline__ void __list_add(struct list_head * new, struct list_head * prev, struct list_head * next)
    {
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
    }

    /**
     * Adicionar uma nova entrada.
     *
     * @new: Nova entrada a ser adicionada.
     * @head: Cabeçalho da lista para adicioná-lo depois.
     *
     * Insira uma nova entrada após o cabeçalho especificado.
     * Isso é bom para implementar pilhas.
     */
    static __inline__ void list_add(struct list_head *new, struct list_head *head)
    {
        __list_add(new, head, head->next);
    }

    /**
     * Adicionar uma nova entrada.
     *
     * @new: Nova entrada a ser adicionada.
     * @head: liste cabeçalhos para adicioná-los antes.
     *
     * Insira uma nova entrada antes do cabeçalho especificado.
     * Isso é útil para implementar filas.
     */
    static __inline__ void list_add_tail(struct list_head *new, struct list_head *head)
    {
        __list_add(new, head->prev, head);
    }

    /**
     * Exclua uma entrada da lista fazendo com que as entradas
     * anterior/seguinte apontem uma para a outra.
     *
     * Isso é apenas para manipulação de lista interna onde já
     * conhecemos as entradas anteriores/seguintes!
     */
    static __inline__ void __list_del(struct list_head * prev, struct list_head * next)
    {
        next->prev = prev;
        prev->next = next;
    }

    /**
     * Exclui a entrada da lista.
     *
     * @entry: o elemento a ser excluído da lista.
     * @Obs: list_empty na entrada não retorna true depois disso,
     *       a entrada está em um estado indefinido.
     */
    static __inline__ void list_del(struct list_head *entry)
    {
        __list_del(entry->prev, entry->next);
    }

    /**
     * Exclui a entrada da lista e a reinicializa.
     *
     * @entry: o elemento a ser excluído da lista.
     */
    static __inline__ void list_del_init(struct list_head *entry)
    {
        __list_del(entry->prev, entry->next);
        INIT_LIST_HEAD(entry); 
    }

    /**
     * Testar se uma lista está vazia.
     *
     * @head: A lista para testar.
     */
    static __inline__ int list_empty(struct list_head *head)
    {
        return head->next == head;
    }

    /**
     * Juntar duas listas.
     *
     * @list: A nova lista para adicionar.
     * @head: O lugar para adicioná-lo na primeira lista.
     */
    static __inline__ void list_splice(struct list_head *list, struct list_head *head)
    {
        struct list_head *first = list->next;

        if (first != list)
        {
            struct list_head *last = list->prev;
            struct list_head *at = head->next;

            first->prev = head;
            head->next = first;

            last->next = at;
            at->prev = last;
        }
    }

    /**
     * Obter a estrutura para esta entrada.
     *
     * @ptr:    O ponteiro &struct list_head.
     * @type:   O tipo da estrutura em que está incorporado.
     * @member: O nome do list_struct dentro da estrutura.
     */
    #define list_entry(ptr, type, member) ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

    /**
     * Iterar sobre uma lista.
     *
     * @pos:  O &struct list_head para usar como um contador de loop.
     * @head: O cabeçalho da sua lista.
     */
    #define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)

    /**
     * Iterar sobre uma lista segura contra a remoção da entrada da lista.
     *
     * @pos:  O &struct list_head para usar como um contador de loop.
     * @n:    Outro &struct list_head para usar como armazenamento temporário.
     * @head: O cabeçalho da sua lista.
     */
    #define list_for_each_safe(pos, n, head) \
        for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#endif

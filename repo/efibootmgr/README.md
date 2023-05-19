Este é o **efibootmgr**, um aplicativo de espaço de usuário Linux para modificar o
gerenciador de inicialização Intel Extensible Firmware Interface (EFI). Este
aplicativo pode criar e destruir entradas de inicialização, alterar a ordem
de inicialização, alterar a próxima opção de inicialização em execução e
muito mais.

Detalhes sobre o EFI Boot Manager estão disponíveis no EFI
Especificação, v1.02 ou mais nova, disponível em: http://localhost/uefi

Observação: o efibootmgr requer que o módulo do kernel efivarfs ou
efivars herdado seja carregado antes do uso.

```
uso: efibootmgr [opções]
        -a | --active          Definir bootnum ativo.
        -A | --inactive        Definir bootnum inativo.
        -b | --bootnum XXXX    Modifique BootXXXX (hex).
        -B | --delete-bootnum  Excluir bootnum.
        -c | --create          Crie uma nova variável bootnum e adicione ao bootorder.
        -d | --disk disk       (Padrões para /dev/sda) contendo carregador.
        -e | --edd [1|3|-1]    Forçar variáveis de criação de EDD 1.0 ou 3.0, ou adivinhar.
        -E | --device num      Número do dispositivo EDD 1.0 (o padrão é 0x80).
        -f | --reconnect       Reconecte os dispositivos após o driver ser carregado.
        -F | --no-reconnect    Não reconecte os dispositivos após o driver ser carregado.
        -g | --gpt             Força o disco com PMBR inválido a ser tratado como GPT.
        -i | --iface name      Crie uma entrada netboot para a interface nomeada.
        -l | --loader name     (Padrões para \elilo.efi).
        -L | --label label     Rótulo de exibição do gerenciador de inicialização (o padrão é "Linux").
        -n | --bootnext XXXX   Defina BootNext como XXXX (hex).
        -N | --delete-bootnext Remover BootNext.
        -o | --bootorder XXXX,YYYY,ZZZZ,...     Defina explicitamente BootOrder (hex).
        -O | --delete-bootorder   Remover BootOrder.
        -p | --part part          (Padrões para 1) contendo carregador.
        -q | --quiet              Fique quieto.
        -t | --timeout seconds    Tempo limite do gerenciador de inicialização.
        -T | --delete-timeout     Excluir valor de tempo limite.
        -u | --unicode | --UCS-2  Passe argumentos extras como UCS-2 (o padrão é ASCII).
        -v | --verbose            Imprimir informações adicionais.
        -V | --version            Versão de retorno e saída.
        -w | --write-signature    Grava assinatura exclusiva no MBR, se necessário.
        -@ | --append-binary-args Acrescentar argumentos variáveis extras de
                                  arquivo (use - para ler de stdin).
```

Uso típico:

O root pode usá-lo para exibir as configurações atuais do Gerenciador de Inicialização.
```
[root@localhost ~]# efibootmgr
BootCurrent: 0004
BootNext: 0003
BootOrder: 0004,0000,0001,0002,0003
Timeout: 30 seconds
Boot0000* Diskette Drive(device:0)
Boot0001* CD-ROM Drive(device:FF)
Boot0002* Hard Drive(Device:80)/HD(Part1,Sig00112233)
Boot0003* PXE Boot: MAC(00D0B7C15D91)
Boot0004* Linux
```

Isso mostra:
**BootCurrent** - a entrada de inicialização usada para iniciar o sistema
em execução no momento.

**BootOrder** - a ordem de inicialização como apareceria no gerenciador de
inicialização. O gerenciador de inicialização tenta inicializar a primeira
entrada ativa nesta lista. Se malsucedido, ele tenta a próxima entrada e
assim por diante.

**BootNext** - a entrada de inicialização que está programada para ser
executada na próxima inicialização. Isso substitui BootOrder apenas
para uma inicialização e é excluído pelo gerenciador de inicialização
após o primeiro uso. Isso permite que você altere o próximo comportamento
de inicialização sem alterar o BootOrder.

**Timeout** - o tempo em segundos entre quando o gerenciador de inicialização
aparece na tela até quando ele escolhe automaticamente o valor de
inicialização de BootNext ou BootOrder.

Cinco entradas de inicialização (0000 - 0004), o sinalizador ativo/inativo
(* significa ativo) e o nome exibido na tela.

Casos de uso alternativos podem ser os seguintes:

1) Um instalador de sistema operacional chamaria `efibootmgr -c`. Isso
   pressupõe que /dev/sda1 é sua partição de sistema EFI e está montada
   em /boot/efi. Isso cria uma nova opção de inicialização, chamada "Linux",
   e a coloca no topo da lista de ordem de inicialização. Opções podem ser
   passadas para modificar o comportamento padrão. O OS Loader padrão é
   elilo.efi.

2) Um administrador de sistema deseja alterar a ordem de inicialização.
   Ela chamaria `efibootmgr -o 3,4` para especificar a inicialização PXE
   primeiro, depois a inicialização do Linux.

3) Um administrador de sistema deseja alterar a ordem de inicialização
   apenas para a próxima inicialização. Ela chamaria `efibootmgr -n 4`
   para especificar que a entrada do Linux seria tomada na próxima
   inicialização.

4) Um administrador de sistema deseja excluir a opção de inicialização
   do Linux do menu. `efibootmgr -b 4 -B` exclui a entrada 4 e a
   remove do BootOrder.

5) Um administrador de sistema deseja criar uma opção de inicialização
   para inicialização de rede (PXE). Você cria a entrada de
   inicialização com: `efibootmgr -c -i eth0 -L netboot`

Por favor, encaminhe quaisquer bugs, recursos, patches, etc. para a equipe de
bootloader do sistema:

   http://localhost/efibootmgr

#
# Android.mk.
#
# Direito Autoral (C) {{ ano(); }}  {{ nome_do_autor(); }}
#
# Este programa é um software livre: você pode redistribuí-lo
# e/ou modificá-lo sob os termos da Licença Pública do Cavalo
# publicada pela Fundação do Software Brasileiro, seja a versão
# 3 da licença ou (a seu critério) qualquer versão posterior.
#
# Este programa é distribuído na esperança de que seja útil,
# mas SEM QUALQUER GARANTIA; mesmo sem a garantia implícita de
# COMERCIABILIDADE ou ADEQUAÇÃO PARA UM FIM ESPECÍFICO. Consulte
# a Licença Pública e Geral do Cavalo para obter mais detalhes.
#
# Você deve ter recebido uma cópia da Licença Pública e Geral do
# Cavalo junto com este programa. Se não, consulte:
#   <http://localhost/licenses>.
#


LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/../Make.version

LOCAL_MODULE := efibootmgr
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_STATIC_LIBRARIES := libefivar
LOCAL_MODULE_PATH := $(TARGET_INSTALLER_OUT)/sbin

LOCAL_CFLAGS := \
    -Werror \
    -Wall \
    -Wextra \
    -Wsign-compare \
    -Wstrict-aliasing \
    -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE \
    -DEFIBOOTMGR_VERSION="\"$(VERSION)\"" \
    -DDEFAULT_LOADER=\"\\\\elilo.efi\"

LOCAL_SRC_FILES := \
    efi.c \
    efibootmgr.c \
    parse_loader_data.c

include $(BUILD_EXECUTABLE)

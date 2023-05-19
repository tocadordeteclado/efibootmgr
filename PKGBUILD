#
# Contribuidor: {{ nome_do_autor(); }}
#

pkgname=efibootmgr
pkgver=18
pkgrel=2
pkgdesc="Aplicativo de espaço do usuário para modificar o EFI Boot Manager"
arch=(x86_64)
url="https://localhost/efibootmgr"
license=(cIO)
depends=(glibc popt)
makedepends=(efivar git)
source=(efibootmgr.tar.gz)
sha512sums=('SKIP')

build()
{
    make libdir=/usr/lib sbindir=/usr/bin EFIDIR=arch -C $pkgname
}

package()
{
    depends+=(libefiboot.so libefivar.so)

    make DESTDIR="$pkgdir" libdir=/usr/lib sbindir=/usr/bin EFIDIR=arch install -C $pkgname
    install -vDm 644 $pkgname/{AUTHORS,README,README.md,TODO} -t "$pkgdir/usr/share/doc/$pkgname/"
}

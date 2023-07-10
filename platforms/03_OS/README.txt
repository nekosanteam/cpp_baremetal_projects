git clone -b kirkstone https://git.yoctoproject.org/poky
. poky/oe-init-build-env build

cat >> conf/local.conf <<CONF_ADD
DL_DIR ?= "${TOPDIR}/../downloads"
MACHINE ?= "qemuarm64"
PACKAGE_CLASSES ?= "package_deb"
CONF_ADD

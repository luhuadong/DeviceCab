#!/bin/sh

LINES=77  # The number of file lines + 1, be careful after modified !!!

BIN_DIR="/usr/bin"
TMP_DIR="/tmp"
ICON_DIR="/usr/share/pixmaps"
CONFIG_DIR="/etc/gbox"
DESKTOP_DIR="/usr/share/applications"

APP_DIR="gbox"

APP="easybench"
BOOT=${APP}.sh
ICON=${APP}.png
CONFIG=${APP}.conf
DESKTOP=${APP}.desktop

CheckPermission() {
	account=`whoami`
	if [ ${account} != "root" ]; then
		echo "${account}, you are NOT the supervisor."
		echo "The root permission is required to run this installer."
		echo "Permission denied."
		exit 1
	fi
}

Unpack() {

	tail -n+${LINES} $0 > ${TMP_DIR}/${APP}.tar.bz2

	echo tar jxf ${TMP_DIR}/${APP}.tar.bz2 -C ${TMP_DIR}
	tar jxf ${TMP_DIR}/${APP}.tar.bz2 -C ${TMP_DIR}

	if [ $? -ne 0 ]; then
		echo "Unpack ${TMP_DIR}/${APP}.tar.bz2 failed"
		echo "Update failed"
		exit 1
	fi
}

Install() {

	if [ ! -d ${CONFIG_DIR} ]; then
		echo mkdir -p ${CONFIG_DIR}
		mkdir -p ${CONFIG_DIR}
	fi
	
	echo cp ${TMP_DIR}/${APP_DIR}/${APP} ${BIN_DIR}
	cp ${TMP_DIR}/${APP_DIR}/${APP} ${BIN_DIR}
	
	echo cp ${TMP_DIR}/${APP_DIR}/${APP}.sh ${BIN_DIR}
	cp ${TMP_DIR}/${APP_DIR}/${APP}.sh ${BIN_DIR}

	echo cp ${TMP_DIR}/${APP_DIR}/${CONFIG} /etc/gbox/
	cp ${TMP_DIR}/${APP_DIR}/${CONFIG} /etc/gbox/

	echo cp ${TMP_DIR}/${APP_DIR}/eepromARMtool ${BIN_DIR}
	cp ${TMP_DIR}/${APP_DIR}/eepromARMtool ${BIN_DIR}

	echo cp ${TMP_DIR}/${APP_DIR}/${ICON} ${ICON_DIR}
	cp ${TMP_DIR}/${APP_DIR}/${ICON} ${ICON_DIR}

	echo cp ${TMP_DIR}/${APP_DIR}/${DESKTOP} ${DESKTOP_DIR}
	cp ${TMP_DIR}/${APP_DIR}/${DESKTOP} ${DESKTOP_DIR}

	echo "Update success"
}

CheckPermission
Unpack
Install
sync

exit 0

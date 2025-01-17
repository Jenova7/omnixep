#!/usr/bin/env bash
# Copyright (c) 2016-2019 The Xep Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

XEPD=${XEPD:-$BINDIR/xepd}
XEPCLI=${XEPCLI:-$BINDIR/xep-cli}
XEPTX=${XEPTX:-$BINDIR/xep-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/xep-wallet}
XEPQT=${XEPQT:-$BINDIR/qt/xep-qt}

[ ! -x $XEPD ] && echo "$XEPD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a XEPVER <<< "$($XEPCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for xepd if --version-string is not set,
# but has different outcomes for xep-qt and xep-cli.
echo "[COPYRIGHT]" > footer.h2m
$XEPD --version | sed -n '1!p' >> footer.h2m

for cmd in $XEPD $XEPCLI $XEPTX $WALLET_TOOL $XEPQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${XEPVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${XEPVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m

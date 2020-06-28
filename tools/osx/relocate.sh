#!/bin/bash
#
# Frontier - A toolkit for creating simple OS-independent user interfaces
# Copyright (C) 2018,2020 Ian Parker <ian@geekprojects.com>
#
# This file is part of Frontier.
#
# Frontier is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Frontier is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
#

BIN=$1
APPDIR=$2/Contents

LOCALLIBS=`otool -l $BIN 2>&1|grep "\/usr\/local"|cut -d' ' -f11`

for LIB in $LOCALLIBS
do
    echo "Library: $LIB"
    LIBNAME=`basename $LIB`
    install_name_tool -change $LIB @executable_path/../Frameworks/$LIBNAME $BIN
    cp $LIB $APPDIR/Frameworks
done


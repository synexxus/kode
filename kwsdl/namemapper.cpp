/*
    This file is part of KDE.

    Copyright (c) 2005 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "namemapper.h"

using namespace KWSDL;

NameMapper::NameMapper()
{
  mKeyWords << "delete" << "class" << "default" << "new" << "not" << "return";
}

QString NameMapper::escape( const QString &name ) const
{
  if ( mKeyWords.contains( name ) )
    return '_' + name;
  else
    return name;
}

QString NameMapper::unescape( const QString &name ) const
{
  if ( name.startsWith( "_" ) )
    return name.mid( 1 );
  else
    return name;
}

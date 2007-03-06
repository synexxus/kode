/*
    This file is part of KXForms.

    Copyright (c) 2007 Andre Duffeck <aduffeck@suse.de>

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

#include "section.h"

#include "manager.h"

#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>

using namespace KXForms;

Section::Section( Manager *m, const QString &label, QWidget *parent )
  : GuiElement( parent ), mManager( m )
{
  QBoxLayout *topLayout = new QHBoxLayout( this );

  mBox = new QGroupBox( label, this );
  topLayout->addWidget( mBox );
  mLayout = new QVBoxLayout( mBox );
}
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

#include "editor.h"
#include "editorwidget.h"
#include "editoraction.h"
#include "changelabelaction.h"
#include "appearanceaction.h"
#include "listaction.h"
#include "positionaction.h"
#include "layoutstyleaction.h"

#include "../manager.h"
#include "../guielement.h"

#include <kactionmenu.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmenu.h>
#include <kapplication.h>
#include <kpixmapeffect.h>

#include <QEvent>
#include <QEventLoop>

using namespace KXForms;

Editor::Editor( Manager *m)
: mEventLoop( new QEventLoop( this ) ), mEditMode( false ), mInEdit( false ),
  mEditorWidget( 0 ), mManager( m )
{
  setupActions();
}

Editor::~Editor()
{
  foreach( EditorAction *a, mActions.values() ) {
    delete a;
  }
}

void Editor::setupActions()
{
  EditorAction *a;

  a = new ChangeLabelAction( this );
  connect( a, SIGNAL(hintGenerated( const Hint & )), 
      SLOT(applyHint( const Hint & )) );
  mActions[ "edit_label" ] = a;

  a = new AppearanceAction( this );
  connect( a, SIGNAL(hintGenerated( const Hint & )), 
      SLOT(applyHint( const Hint & )) );
  mActions[ "edit_appearance" ] = a;

  a = new ListAction( this );
  connect( a, SIGNAL(hintGenerated( const Hint & )), 
      SLOT(applyHint( const Hint & )) );
  mActions[ "edit_list" ] = a;

  a = new PositionAction( this );
  connect( a, SIGNAL(hintGenerated( const Hint & )), 
      SLOT(applyHint( const Hint & )) );
  mActions[ "edit_position" ] = a;

  a = new LayoutStyleAction( this );
  connect( a, SIGNAL(hintGenerated( const Hint & )), 
      SLOT(applyHint( const Hint & )) );
  mActions[ "edit_layoutstyle" ] = a;
}

void Editor::registerElement( GuiElement *element )
{
  kDebug() << k_funcinfo << "Registered element " << element->ref().toString() << endl;
//   element->editorWidget()->installEventFilter( this );
  mElements.append( element );
}

void Editor::setEditMode( bool enabled )
{
  kDebug() << k_funcinfo << "Setting editmode to " << enabled << endl;
  mEditMode = enabled;

  if( enabled ) {
    GuiElement::List list = mManager->currentGui()->elements();
    QWidget *w = list.first()->widget()->parentWidget();
    mEditorWidget = new EditorWidget( this, w );
    mEditorWidget->setGuiElements( list );
    mEditorWidget->show();
  } else {
    mEditorWidget->hide();
    mEditorWidget->deleteLater();
  } 

//   foreach( GuiElement *e, mElements ) {
//     e->setEditMode( enabled );
//   }
}

void Editor::toggleEditMode()
{
  setEditMode( !mEditMode );
}

void Editor::performAction( const QString &actionId, EditorWidget *w )
{
  kDebug() << k_funcinfo << "Performing action " << actionId << endl;

  EditorAction *a = mActions[ actionId ];
  if( !a )
    return;

  a->perform( w );
}

void Editor::applyHint( const Hint &h )
{
  kDebug() << k_funcinfo << endl;

  mHints.dump();
  mHints.merge( h );
  mHints.dump();

  mElements.clear();
  mEditMode = false;
  emit hintsChanged( mHints );
}

bool Editor::eventFilter( QObject *obj, QEvent *e )
{
  if (e->type() == QEvent::MouseButtonRelease) {
    EditorWidget *w = dynamic_cast<EditorWidget *>( obj );
    if( !w )
      return false;

    mChosenEditorWidget = w;
    if( mEventLoop->isRunning() ) {
      mEventLoop->exit();
    }
    return true;
  } else {
    return false;
  }
}

EditorWidget *Editor::selectWidget()
{
  kDebug() << k_funcinfo << endl;

  mChosenEditorWidget = 0;
  mEventLoop->exec();

  return mChosenEditorWidget;
}

#include "editor.moc"
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
#ifndef EDITOR_H
#define EDITOR_H

#include "../hints.h"

#include <QObject>
#include <QList>
#include <QMap>

class KActionMenu;
class QEventLoop;
class QLabel;

namespace KXForms {

class GuiElement;
class EditorWidget;
class EditorAction;
class Manager;

class Editor : public QObject
{
  Q_OBJECT
  public:
    enum ActionType{
      CommonActions = 0x1,
      ListActions = 0x2,
      AppearanceActions = 0x4
    };
    Q_DECLARE_FLAGS(ActionTypes, ActionType)


    Editor( Manager *);
    ~Editor();

    void registerElement( GuiElement * );
    bool editMode() const { return mEditMode; }

    void beginEdit() { mInEdit = true; }
    void finishEdit() { mInEdit = false; }

    bool inEdit() const { return mInEdit; }

    KActionMenu *actionMenu( EditorWidget *w );

    void performAction( const QString &actionId, EditorWidget *w );

    void addHints( const Hints &h ) { mHints.merge( h ); }
    Hints hints() const { return mHints; }

  Q_SIGNALS:
    void hintsChanged( const Hints &h );

  public Q_SLOTS:
    void setEditMode( bool );
    void toggleEditMode();

    EditorWidget *selectWidget();

  protected:
    bool eventFilter( QObject *obj, QEvent *e );

  private Q_SLOTS:
    void applyHint( const Hint &h );

  private:
    void setupActions();

  private:
    QList< GuiElement *> mElements;
    QMap< QString, EditorAction * > mActions;
    QEventLoop *mEventLoop;
    bool mEditMode;
    bool mInEdit;

    EditorWidget *mEditorWidget;

    EditorWidget *mChosenEditorWidget;

    Hints mHints;

    Manager *mManager;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(KXForms::Editor::ActionTypes)
#endif
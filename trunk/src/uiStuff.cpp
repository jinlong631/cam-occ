/***************************************************************************
 *   Copyright (C) 2009 by Mark Pictor					   *
 *   mpictor@gmail.com							   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "uiStuff.h"
#include "cam.h"

#include <string>
#include <ostream>

#include <QMessageBox>
#include <QIcon>
#include <QAction>
#include <QMenuBar>


#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Handle_AIS_InteractiveObject.hxx>
#include <AIS_Trihedron.hxx>


uiStuff::uiStuff() {
	errors = 0;
	theWindow = 0;
}

uiStuff::~uiStuff() {
}

void uiStuff::init(QoccHarnessWindow* window) {
	theWindow = window;
	slotNeutralSelection();
	addSelectionWidgets();
}

void uiStuff::redraw() {
	theWindow->getView()->Redraw();
}


void uiStuff::getSelection() {
	selectedShapes.clear();
	for ( theWindow->getContext()->InitSelected(); theWindow->getContext()->MoreSelected(); theWindow->getContext()->NextSelected() ) {
                Handle_AIS_InteractiveObject IO = theWindow->getContext()->Interactive();
                if (IO->IsKind(STANDARD_TYPE(AIS_Trihedron)) || !theWindow->getContext()->HasSelectedShape())
                {
                        theWindow->getContext()->ClearSelected();
                        break;
                }
                selectedShapes.push_back(theWindow->getContext()->SelectedShape());
	}
}



//normally called like this: debugMsg("error string",__FILE__,__LINE__);
void uiStuff::debugMsg(QString s, QString f, int l) {
	errors++;
	cerr << "Error  #" << errors << ": " << s.toStdString() << "\n\tin file " << f.toStdString() << " at line " << l << "." << endl;
}

void uiStuff::infoMsg( QString title, QString message ) {
	QMessageBox::information(theWindow,title,message);
}

void uiStuff::infoMsg( QString message ) {
	QMessageBox::information(theWindow,"Camocc2",message);
}

QString uiStuff::toString(float a,float b, float c) {
	return QString("%1, %2, %3").arg(a).arg(b).arg(c);
}

QString uiStuff::toString(gp_Pnt p) {
	return QString("%1, %2, %3").arg(p.X()).arg(p.Y()).arg(p.Z());
}

void uiStuff::slotNeutralSelection()
{
  theWindow->getContext()->CloseAllContexts();
}

void uiStuff::slotVertexSelection()
{
  theWindow->getContext()->CloseAllContexts();
  theWindow->getContext()->OpenLocalContext();
  theWindow->getContext()->ActivateStandardMode(TopAbs_VERTEX);
}

void uiStuff::slotEdgeSelection()
{
  theWindow->getContext()->CloseAllContexts();
  theWindow->getContext()->OpenLocalContext();
  theWindow->getContext()->ActivateStandardMode(TopAbs_EDGE);
}

void uiStuff::slotFaceSelection()
{
  theWindow->getContext()->CloseAllContexts();
  theWindow->getContext()->OpenLocalContext();
  theWindow->getContext()->ActivateStandardMode(TopAbs_FACE);
}

void uiStuff::slotSolidSelection()
{
  theWindow->getContext()->CloseAllContexts();
  theWindow->getContext()->OpenLocalContext();
  theWindow->getContext()->ActivateStandardMode(TopAbs_SOLID);
}

void uiStuff::addSelectionWidgets() {
	QMenu *selectMenu;
	selectMenu = new QMenu("Select");
	theWindow->menuBar()->insertMenu(theWindow->getHelpMenu(),selectMenu);  //put this menu BEFORE the help menu
//	theWindow->menuBar()->addMenu(selectMenu);

	QAction *selectNeutralAction;
	selectNeutralAction = new QAction("Neutral", this);
	//selectNeutralAction->setShortcut(QString("Ctrl+N"));
	selectNeutralAction->setStatusTip("Select Nothing");
	connect(selectNeutralAction, SIGNAL(triggered()), this, SLOT(slotNeutralSelection()));
	selectMenu->addAction( selectNeutralAction );

	QAction *selectVertexAction;
	selectVertexAction = new QAction("Vertex", this);
	selectVertexAction->setStatusTip("Select Vertices");
	connect(selectVertexAction, SIGNAL(triggered()), this, SLOT(slotVertexSelection()));
	selectMenu->addAction( selectVertexAction );

	QAction *selectEdgeAction;
	selectEdgeAction = new QAction("Edge", this);
	selectEdgeAction->setStatusTip("Select Edges");
	connect(selectEdgeAction, SIGNAL(triggered()), this, SLOT(slotEdgeSelection()));
	selectMenu->addAction( selectEdgeAction );

	QAction *selectFaceAction;
	selectFaceAction = new QAction("Face", this);
	selectFaceAction->setStatusTip("Select Faces");
	connect(selectFaceAction, SIGNAL(triggered()), this, SLOT(slotFaceSelection()));
	selectMenu->addAction( selectFaceAction );

	QAction *selectSolidAction;
	selectSolidAction = new QAction("Solid", this);
	selectSolidAction->setStatusTip("Select Solids");
	connect(selectSolidAction, SIGNAL(triggered()), this, SLOT(slotSolidSelection()));
	selectMenu->addAction( selectSolidAction );
}

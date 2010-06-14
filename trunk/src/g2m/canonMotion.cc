/***************************************************************************
 *   Copyright (C) 2010 by Mark Pictor                                     *
 *   mpictor@gmail.com                                                     *
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
//for LINEAR_TRAVERSE, LINEAR_FEED, ARC_FEED
#include <string>
#include <limits.h>

#include <Precision.hxx>

#include "canonMotion.hh"
#include "canonLine.hh"

canonMotion::canonMotion(std::string canonL, machineStatus prevStatus): canonLine(canonL,prevStatus) {
  status.setEndPose(getPoseFromCmd());
}

///for LINEAR_* and ARC_FEED, first 3 are always xyz and last 3 always abc
gp_Ax1 canonMotion::getPoseFromCmd() {
  double x,y,z,a,b,c;
  
  //need 3,4,5,and -3,-2,-1
  x = tok2d(3);
  y = tok2d(4);
  z = tok2d(5);
  gp_Pnt p(x,y,z);
  
/* FIXME
  uint s = canonTokens.size(); //a,b,c are last 3 numbers
  c = tok2d(s-1);
  b = tok2d(s-2);
  a = tok2d(s-3);
  //now how to convert those angles to a unit vector (i.e. gp_Dir)?
*/  
  //for now we take the easy way out
  gp_Dir d(0,0,1); //vertical
  assert (a+b+c < 3.0 * Precision::Confusion());
  return gp_Ax1(p,d);
}


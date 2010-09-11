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

#ifndef GTOM_HH
#define GTOM_HH

#include <vector>

#include <QString>
#include <QObject>
#include <QMutex>

#include "canonLine.hh"
#include "machineStatus.hh"
//#include "dispShape.hh"

/**
\class g2m
\brief This class does the high level stuff for creating a model from gcode.
It runs the interpreter, and creates a canonLine object for each canonical command generated by the interpreter. It also does error checking and stores the cannonLines. It calls methods on each canonLine object to display it. Eventually it will enable the user to see which gcode line creates which bit of the path, and vice versa.
*/
class g2m: public QObject {
  Q_OBJECT;
  public:
    g2m();
    void start (QString file);
    bool isOK() {return success;};
  public slots:
    void slotModelFromFile();
  protected:
    bool fromCmdLine;
    void interpret();
    bool processCanonLine(std::string l);
    bool success;
    //inline void infoMsg(QString s) {infoMsg(s.toStdString();};
    void infoMsg(std::string s);
    void sleepSecond();
    static std::vector<canonLine*> lineVector;
//    std::vector<dispShape*> dispVector;
    QString file;
    bool debug;
    //void test(); //FIXME: temporary
    //void makeSolids(uint start=0, uint incr=1);
    void statusBarUp(std::string s, double avgtime);

    /******************************** THREAD-RELATED ********************************/
    ///is interpreter done? must be false until we're done adding to lineVector
    static bool interpDone;
    std::list< pthread_t* > threadIdList;
    ///cpu count for multithreading. this is the size of the array
    long mthreadCpuCnt;
//    void startThreads();
    void createThreads();
    void joinThreads();
    void checkIfSafeForThreading();
    static void* makeSolidsThread(void * v);
    static void threadSafeSleep();
    static uint nextAvailInVec(bool onlyWatch = false);
    static uint getVecSize();
    static QMutex vecModMutex;   //used when a canonLine is pushed onto vector, and in getVecSize()
    static QMutex vecGrowMutex;  //used in & blocks makeSolidsThread only, blocks while waiting for vector to grow

};

#endif //GTOM_HH

#include "Matrix.h"

Matrix::Matrix() {

  // parto dal centro
  r[0] = r[1] = c[0] = c[1] = 8;
  floor = 0;
  dir = 0;
  rise = false;
  keep = true;
  cont = 0;
}

void Matrix::check(float tempDx, float tempSx, float distDx, float distSx, float inclination, byte color) { /// Controlla lo stato della cella
    if (!maze[floor][r[floor]][c[floor]].isVisited()) cont++;
    if (inclination >= 10 || inclination <= -10) {
      if (!rise) {
        back();
        floor = !floor;
      }
      rise = true;
    } else rise = false;
    if (!rise) {
      maze[floor][r[floor]][c[floor]].visited();
      maze[floor][r[floor]][c[floor]].direction(dir);
      /*maze[floor][r[floor]][c[floor]].hot = tempdx > 68 || tempsx > 60;*/
      bool hotDx = tempDx >= DELTATEMP && distDx < DISTWALL;
      bool hotSx = tempSx >= DELTATEMP && distSx < DISTWALL;
      if (hotDx || hotSx) maze[floor][r[floor]][c[floor]].hot();
      if (color == 1 && !maze[floor][r[floor]][c[floor]].isCheckPoint()) {
        maze[floor][r[floor]][c[floor]].checkPoint();
        checkr = r[floor];
        checkc = c[floor];
        checkfl = floor;
      } else if (color == 2) maze[floor][r[floor]][c[floor]].black();
    }
    keep = cont < NCELLS || !(floor == 0 && r[floor] == 8 && c[floor] == 8);
  }

  void Matrix::changeFloor() {
    floor = !floor;
  }

  bool Matrix::frontCheck() { /// Restituisce vero se la cella davanti al bot è già stata visitata
    go();
    bool ris = maze[floor][r[floor]][c[floor]].isVisited();
    back();
    return ris;
  }

  bool Matrix::frontBlack() { /// Restituisce vero se la cella davanti al bot è nera
    go();
    bool ris = maze[floor][r[floor]][c[floor]].isBlack();
    back();
    return ris;
  }

  void Matrix::reset() {
    r[floor] = checkr;
    c[floor] = checkc;
    floor = checkfl;
  }

  void Matrix::go() {
    if (!rise) {
      switch (dir) {
        case 0:
        r[floor]--;
        break;
        case 1:
        c[floor]++;
        break;
        case 2:
        r[floor]++;
        break;
        case 3:
        c[floor]--;
        break;
      }
    }
    keep = cont < NCELLS || !(floor == 0 && r[floor] == 8 && c[floor] == 8);
  }

  void Matrix::back() {
    switch (dir) {
      case 0:
      r[floor]++;
      break;
      case 1:
      c[floor]--;
      break;
      case 2:
      r[floor]--;
      break;
      case 3:
      c[floor]++;
      break;
    }
  }

  byte Matrix::getDir(float dx, float front, float sx) { /// Ritorna 1 per destra, 2 per avanti, 3 per sinistra, 4 dietro
    byte saved_dir = dir;
    byte pdir = 4;
    rotate(false);
    if (!frontCheck() && !frontBlack() && dx > DISTWALL) {
      pdir = 1;
    } else {
      rotate(true);
      if (!frontCheck() && !frontBlack() && front > DISTWALL) {
        pdir = 2;
      } else {
        rotate(true);
        if (!frontCheck() && !frontBlack() && sx > DISTWALL) {
          pdir = 3;
        } else { // giusto
          dir = saved_dir;
          maze[floor][r[floor]][c[floor]].direction(saved_dir);
          rotate(false);
          if (!frontBlack() && dx > DISTWALL) {
            pdir = 1;
          } else {
            rotate(true);
            if (!frontBlack() && front > DISTWALL) {
              pdir = 2;
            } else {
              rotate(true);
              if (!frontBlack() && sx > DISTWALL) {
                pdir = 3;
              }
            }
          }
        }
      }
    }
    dir = saved_dir;
    maze[floor][r[floor]][c[floor]].direction(saved_dir);
    return pdir;
  }

  void Matrix::rotate(bool direction) { /// Cambia direzione nella matrice (true = sinistra, false = destra)
    if (direction)
    dir = dir == 0 ? 3 : dir - 1;
    else
    dir = dir == 3 ? 0 : dir + 1;
    maze[floor][r[floor]][c[floor]].direction(dir);
  }

  bool Matrix::isHot() {
    return maze[floor][r[floor]][c[floor]].isHot();
  }

  bool Matrix::isVisited() {
    return maze[floor][r[floor]][c[floor]].isVisited();
  }

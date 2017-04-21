#include "Matrix.h"

Matrix::Matrix() {
  r[0] = r[1] = c[0] = c[1] = 8; // Both fool start from the center
  floor = 0;
  dir = 0;
  keep = true;
  cont = 0;
}

void Matrix::check(float tempDx, float tempSx, float distDx, float distSx, byte color) {
  if (!maze[floor][r[floor]][c[floor]].isVisited()) cont++;

  maze[floor][r[floor]][c[floor]].visited();
  maze[floor][r[floor]][c[floor]].direction(dir);

  bool hotDx = tempDx >= DELTATEMP && distDx < DISTWALL;
  bool hotSx = tempSx >= DELTATEMP && distSx < DISTWALL;

  if (hotDx || hotSx) maze[floor][r[floor]][c[floor]].hot();
  if (color == 1 && !maze[floor][r[floor]][c[floor]].isCheckPoint()) {
    maze[floor][r[floor]][c[floor]].checkPoint();
    checkr = r[floor];
    checkc = c[floor];
    checkfl = floor;
  } else if (color == 2) maze[floor][r[floor]][c[floor]].black();

  keep = cont < NCELLS || !(floor == 0 && r[floor] == 8 && c[floor] == 8);
}

void Matrix::changeFloor() {
  floor = !floor;
}

bool Matrix::frontCheck() {
  go();
  bool ris = maze[floor][r[floor]][c[floor]].isVisited();
  back();
  return ris;
}

bool Matrix::frontBlack() {
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

byte Matrix::getDir(float dx, float front, float sx) { // 1 = rigth, 2 = front, 3 = left, 4 = back
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

void Matrix::rotate(bool direction) { // Change the direction, true = left, false = rigth)
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

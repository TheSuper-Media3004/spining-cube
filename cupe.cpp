#include <iostream>
#include <cstring>
#include <thread>
#include <cmath>
#include "cube.h"

using namespace std;
using namespace chrono;

int main(int argc, char const *argv[])
{
  cout << "\x1b[2J";
  while (1)
  {
    fill(buffer, buffer + AREA, BACKGROUND_ASCII_CODE);
    memset(z_buffer, 0, AREA * 4);
    // TODO: Use fill() instead of memset(). fill(z_buffer, z_buffer + AREA * 4, 0);

    // Looping through X
    for (float cube_x = -CUBE_WIDTH; cube_x < CUBE_WIDTH; cube_x += INCREMENT_SPEED)
    {
      // Looping through Y
      for (float cube_y = -CUBE_WIDTH; cube_y < CUBE_WIDTH; cube_y += INCREMENT_SPEED)
      {
        calculateForSurface(cube_x, cube_y, -CUBE_WIDTH, '@');
        calculateForSurface(CUBE_WIDTH, cube_y, cube_x, '$');
        calculateForSurface(-CUBE_WIDTH, cube_y, -cube_x, '~');
        calculateForSurface(-cube_x, cube_y, CUBE_WIDTH, '#');
        calculateForSurface(cube_x, -CUBE_WIDTH, -cube_y, ';');
        calculateForSurface(cube_x, CUBE_WIDTH, cube_y, '+');
      }
    }
    cout << "\x1b[H";
    for (int k = 0; k < AREA; k++)
      cout << ((k % WIDTH) ? buffer[k] : '\n');
    A += INCREMENT_ANGLE;
    B += INCREMENT_ANGLE;
    this_thread::sleep_for(microseconds(SLEEP_TIME));
  }
  return 0;
}

float calculateX(int i, int j, int k)
{
  return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k)
{
  return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k)
{
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cube_x, float cube_y, float cube_z, int ch)
{
  // ***** Rotated Coordinate Calculation *****
  // x, y, and z are updated by calculating the rotated coordinates of the point in three-dimensional space.
  // These coordinates are obtained by calling the functions calculateX, calculateY, and calculateZ.
  x = calculateX(cube_x, cube_y, cube_z);
  y = calculateY(cube_x, cube_y, cube_z);
  z = calculateZ(cube_x, cube_y, cube_z) + DISTANCE_FROM_CAM;

  // ***** Projected Coordinate Calculation *****
  // ooz is calculated as the inverse of the z-coordinate (1/z). This is used to take into account
  // perspective and adjust the position of the point according to its distance from the camera.
  ooz = 1 / z;

  // xp and yp are calculated as the projected coordinates on the screen. The formula takes into account
  // the scale factor K1, the inverse of the z-coordinate, and the rotated coordinates.
  xp = (int)(WIDTH / 2 + K1 * ooz * x * 2);
  yp = (int)(HEIGHT / 2 + K1 * ooz * y);

  // ***** Z-Buffer and Buffer Update *****
  // It is calculated as the index in the z_buffer and buffer arrays corresponding to the position on the screen where a point is to be drawn.
  idx_buffer = xp + yp * WIDTH;

  // The index is checked to see if it is within the array limits.
  // If so, the value of ooz is compared to the existing value in the z-buffer for that position.
  // If ooz is greater, the z-buffer is updated and the ch character is placed in the buffer at that position.
  if (idx_buffer >= 0 && idx_buffer < AREA)
  {
    if (ooz > z_buffer[idx_buffer])
    {
      z_buffer[idx_buffer] = ooz;
      buffer[idx_buffer] = ch;
    }
  }
}

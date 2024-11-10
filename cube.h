#if !defined(CUBE_H)
#define CUBE_H

float A, B, C;  
float x, y, z; 
float ooz;      
int xp, yp;      
int idx_buffer; 
// Constants
const int WIDTH = 75, HEIGHT = 30;     
const int AREA = WIDTH * HEIGHT;       
const int SLEEP_TIME = 1000;          
const int DISTANCE_FROM_CAM = 50;       
const float CUBE_WIDTH = 7;           
const float INCREMENT_SPEED = 0.5;     
const float INCREMENT_ANGLE = 0.005;    
const float K1 = 40;                   
const char BACKGROUND_ASCII_CODE = ' '; 

char buffer[AREA];    
float z_buffer[AREA]; 
float calculateZ(int i, int j, int k);
float calculateX(int i, int j, int k);
float calculateY(int i, int j, int k);

void calculateForSurface(float cube_x, float cube_y, float cube_z, int ch);

#endif // CUBE_H

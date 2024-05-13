/*
 * points.c
 *
 *  Created on: Dec 13, 2023
 *      Author: Sander
 */

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "points.h"
#include "math.h"

void pointInit(){
	srand(HAL_GetTick());
}


//https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
point randPoint(){
	point p;
	p.x=((rand()*HAL_GetTick())%220)+10; // int vahemikus 10 kuni 230
	p.y=((rand()*HAL_GetTick())%300)+10;
	return p;
}

uint16_t y(uint16_t x, point p1, point p2){
	return (p2.y-p1.y)/(p2.x-p1.x)*(x-p2.x)+p1.y;
}

//https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
uint16_t dist(point p1, point p2, point p){
	float px=p2.x-p1.x;
	float py=p2.y-p1.y;
	float temp=(px*px)+(py*py);
	float u=((p.x - p1.x) * px + (p.y - p1.y) * py) / (temp);
	if(u>1){
		u=1;
	}
	else if(u<0){
		u=0;
	}
	float x = p1.x + u * px;
	float y = p1.y + u * py;

	float dx = x - p.x;
	float dy = y - p.y;
	double dist = sqrt(dx*dx + dy*dy);
	return (uint16_t)dist;
//	  uint16_t A = p.x - p1.x;
//	  uint16_t B = p.y - p1.y;
//	  uint16_t C = p2.x - p1.x;
//	  uint16_t D = p2.y - p1.y;
//
//	  uint16_t len_sq = C * C + D * D;
//	  float param = -1;
//	  if (len_sq != 0) //in case of 0 length line
//		  uint16_t dot = A * C + B * D;
//	      param = dot / len_sq;
//
//	  float xx, yy;
//
//	  if (param < 0) {
//	    xx = p1.x;
//	    yy = p1.y;
//	  }
//	  else if (param > 1) {
//	    xx = p2.x;
//	    yy = p2.y;
//	  }
//	  else {
//	    xx = p1.x + param * C;
//	    yy = p1.y + param * D;
//	  }
//
//	  float dx = p.x - xx;
//	  float dy = p.y - yy;
//	  return (uint16_t) sqrt(dx * dx + dy * dy);
}






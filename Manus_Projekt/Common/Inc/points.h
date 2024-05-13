/*
 * points.h
 *
 *  Created on: Dec 13, 2023
 *      Author: Sander
 */

#ifndef INC_POINTS_H_
#define INC_POINTS_H_

#include <stdint.h>

typedef struct{
	uint16_t x;
	uint16_t y;
} point;

void pointInit();
point randPoint();
uint16_t dist(point p1, point p2, point p);

#endif /* INC_POINTS_H_ */

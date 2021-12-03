/*
 * hbplv1_encode.h
 *
 *  Created on: 2020年2月2日
 *      Author: tom
 *      https://github.com/macos2
 *      https://gitee.com/macos2
 *      the core encode program is writed by Dave Coffin: http://www.dechifro.org/hbpl
 */

#ifndef HBPLV1_ENCODE_H_
#define HBPLV1_ENCODE_H_

#include <stdio.h>
#include <stdbool.h>
#include "hbplv1_enum.h"

typedef struct{
	size_t len;
	unsigned char *image;
	int width,height;
}page_data;

static char Clip[]={0x08,0x08,0x08,0x08};

int hbplv1_do_file(FILE *fp,size_t *num_of_page,size_t *num_of_page_limt,page_data ***set_of_page) ;
page_data* hbplv1_encode_page(int color, int width, int height,char *image);
#endif /* HBPLV1_ENCODE_H_ */

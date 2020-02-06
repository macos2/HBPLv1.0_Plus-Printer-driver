/*
 * hbplv1_template.h
 *
 *  Created on: 2020年1月28日
 *      Author: tom
 *      https://github.com/macos2
 *      https://gitee.com/macos2
 */

#ifndef HBPLV1_TEMPLATE_H_
#define HBPLV1_TEMPLATE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hbplv1_enum.h"

#define S_OFF "OFF"
#define S_ON "ON"
#define S_LONGEDGE "LONGEDGE"
#define S_SHORTEDGE "SHORTEDGE"
//Render Model 打印模式
//grayscale or color
//灰阶 或 彩色
static char *render_model_color =\
 "@PJL SET RENDERMODE=COLOR\n"
		"@PJL SET JOBATTR=\"@BSPM=OFF\"\n"
		"@PJL SET JOBATTR=\"@TRAP=ON\"\n";

static char *render_model_grayscale =\
 "@PJL SET RENDERMODE=GRAYSCALE\n";

//Render Quality 打印质量
//normal	standard	fineness		gradation
//常规		标准			精细				高色阶
static char *color_normal =\
 "@PJL SET JOBATTR=\"@TCPR=11\"\n"
		"@PJL SET JOBATTR=\"@TUCR=11\"\n"
		"@PJL SET JOBATTR=\"@TTRC=11\"\n"
		"@PJL SET JOBATTR=\"@TSCR=11\"\n"
		"@PJL SET JOBATTR=\"@GCPR=11\"\n"
		"@PJL SET JOBATTR=\"@GUCR=11\"\n"
		"@PJL SET JOBATTR=\"@GTRC=11\"\n"
		"@PJL SET JOBATTR=\"@GSCR=11\"\n"
		"@PJL SET JOBATTR=\"@ICPR=12\"\n"
		"@PJL SET JOBATTR=\"@IUCR=12\"\n"
		"@PJL SET JOBATTR=\"@ITRC=12\"\n"
		"@PJL SET JOBATTR=\"@ISCR=12\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *color_standard =\
 "@PJL SET JOBATTR=\"@TCPR=11\"\n"
		"@PJL SET JOBATTR=\"@TUCR=11\"\n"
		"@PJL SET JOBATTR=\"@TTRC=62\"\n"
		"@PJL SET JOBATTR=\"@TSCR=62\"\n"
		"@PJL SET JOBATTR=\"@GCPR=11\"\n"
		"@PJL SET JOBATTR=\"@GUCR=11\"\n"
		"@PJL SET JOBATTR=\"@GTRC=62\"\n"
		"@PJL SET JOBATTR=\"@GSCR=62\"\n"
		"@PJL SET JOBATTR=\"@ICPR=12\"\n"
		"@PJL SET JOBATTR=\"@IUCR=12\"\n"
		"@PJL SET JOBATTR=\"@ITRC=62\"\n"
		"@PJL SET JOBATTR=\"@ISCR=62\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *color_fineness =\
 "@PJL SET JOBATTR=\"@TCPR=13\"\n"
		"@PJL SET JOBATTR=\"@TUCR=13\"\n"
		"@PJL SET JOBATTR=\"@TTRC=61\"\n"
		"@PJL SET JOBATTR=\"@TSCR=61\"\n"
		"@PJL SET JOBATTR=\"@GCPR=13\"\n"
		"@PJL SET JOBATTR=\"@GUCR=13\"\n"
		"@PJL SET JOBATTR=\"@GTRC=61\"\n"
		"@PJL SET JOBATTR=\"@GSCR=61\"\n"
		"@PJL SET JOBATTR=\"@ICPR=14\"\n"
		"@PJL SET JOBATTR=\"@IUCR=14\"\n"
		"@PJL SET JOBATTR=\"@ITRC=61\"\n"
		"@PJL SET JOBATTR=\"@ISCR=61\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *color_gradation =\
 "@PJL SET JOBATTR=\"@TCPR=13\"\n"
		"@PJL SET JOBATTR=\"@TUCR=13\"\n"
		"@PJL SET JOBATTR=\"@TTRC=63\"\n"
		"@PJL SET JOBATTR=\"@TSCR=63\"\n"
		"@PJL SET JOBATTR=\"@GCPR=13\"\n"
		"@PJL SET JOBATTR=\"@GUCR=13\"\n"
		"@PJL SET JOBATTR=\"@GTRC=63\"\n"
		"@PJL SET JOBATTR=\"@GSCR=63\"\n"
		"@PJL SET JOBATTR=\"@ICPR=14\"\n"
		"@PJL SET JOBATTR=\"@IUCR=14\"\n"
		"@PJL SET JOBATTR=\"@ITRC=63\"\n"
		"@PJL SET JOBATTR=\"@ISCR=63\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *grayscale_normal =\
 "@PJL SET JOBATTR=\"@TCPR=33\"\n"
		"@PJL SET JOBATTR=\"@TUCR=33\"\n"
		"@PJL SET JOBATTR=\"@TTRC=33\"\n"
		"@PJL SET JOBATTR=\"@TSCR=33\"\n"
		"@PJL SET JOBATTR=\"@GCPR=33\"\n"
		"@PJL SET JOBATTR=\"@GUCR=33\"\n"
		"@PJL SET JOBATTR=\"@GTRC=33\"\n"
		"@PJL SET JOBATTR=\"@GSCR=33\"\n"
		"@PJL SET JOBATTR=\"@ICPR=34\"\n"
		"@PJL SET JOBATTR=\"@IUCR=34\"\n"
		"@PJL SET JOBATTR=\"@ITRC=34\"\n"
		"@PJL SET JOBATTR=\"@ISCR=34\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *grayscale_standard =\
 "@PJL SET JOBATTR=\"@TCPR=33\"\n"
		"@PJL SET JOBATTR=\"@TUCR=33\"\n"
		"@PJL SET JOBATTR=\"@TTRC=65\"\n"
		"@PJL SET JOBATTR=\"@TSCR=65\"\n"
		"@PJL SET JOBATTR=\"@GCPR=33\"\n"
		"@PJL SET JOBATTR=\"@GUCR=33\"\n"
		"@PJL SET JOBATTR=\"@GTRC=65\"\n"
		"@PJL SET JOBATTR=\"@GSCR=65\"\n"
		"@PJL SET JOBATTR=\"@ICPR=34\"\n"
		"@PJL SET JOBATTR=\"@IUCR=34\"\n"
		"@PJL SET JOBATTR=\"@ITRC=65\"\n"
		"@PJL SET JOBATTR=\"@ISCR=65\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *grayscale_fineness =\
 "@PJL SET JOBATTR=\"@TCPR=33\"\n"
		"@PJL SET JOBATTR=\"@TUCR=33\"\n"
		"@PJL SET JOBATTR=\"@TTRC=64\"\n"
		"@PJL SET JOBATTR=\"@TSCR=64\"\n"
		"@PJL SET JOBATTR=\"@GCPR=33\"\n"
		"@PJL SET JOBATTR=\"@GUCR=33\"\n"
		"@PJL SET JOBATTR=\"@GTRC=64\"\n"
		"@PJL SET JOBATTR=\"@GSCR=64\"\n"
		"@PJL SET JOBATTR=\"@ICPR=34\"\n"
		"@PJL SET JOBATTR=\"@IUCR=34\"\n"
		"@PJL SET JOBATTR=\"@ITRC=64\"\n"
		"@PJL SET JOBATTR=\"@ISCR=64\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *grayscale_gradation =\
 "@PJL SET JOBATTR=\"@TCPR=33\"\n"
		"@PJL SET JOBATTR=\"@TUCR=33\"\n"
		"@PJL SET JOBATTR=\"@TTRC=66\"\n"
		"@PJL SET JOBATTR=\"@TSCR=66\"\n"
		"@PJL SET JOBATTR=\"@GCPR=33\"\n"
		"@PJL SET JOBATTR=\"@GUCR=33\"\n"
		"@PJL SET JOBATTR=\"@GTRC=66\"\n"
		"@PJL SET JOBATTR=\"@GSCR=66\"\n"
		"@PJL SET JOBATTR=\"@ICPR=34\"\n"
		"@PJL SET JOBATTR=\"@IUCR=34\"\n"
		"@PJL SET JOBATTR=\"@ITRC=66\"\n"
		"@PJL SET JOBATTR=\"@ISCR=66\"\n"
		"@PJL SET JOBATTR=\"@TDFT=0\"\n"
		"@PJL SET JOBATTR=\"@GDFT=0\"\n"
		"@PJL SET JOBATTR=\"@IDFT=0\"\n";

static char *job_start =\
 "\x1b%-12345X@PJL USTATUS DEVICE=ON\r\n"
		"@PJL USTATUS JOB=ON\r\n"
		"@PJL USTATUS PAGE=ON\r\n"
		"@PJL INFO STATUS\r\n"
		"@PJL JOB NAME=\"034445534B546E20006FD71A\"\r\n";

static char *job_end =\
 "@PJL EOJ NAME=\"034445534B546E20006FD71A\"\r\n\x1b"
		"%-12345X";

static char *statusoff =\
 "\x1b%-12345X@PJL USTATUSOFF\r\n\x1b"
		"%-12345X";

static char *iwside2start = "@PJL SET IWASIDE2START=%d\n"; //配合双面打印，第几页开始要求反手动翻页打印背面

static char *head_template =\
 "@PJL JOB MODE=PRINTER\n"
		"@PJL SET STRINGCODESET=UTF8\n"
		"@PJL COMMENT DATE=%s\n" //date 日期 MM/DD/YYYY
		"@PJL COMMENT TIME=%s\n"//time 时间 hh:mm:ss
		"@PJL COMMENT DNAME=%s\n"//filename 文件名
		"%s"//iwside2start配合双面打印，第几页开始要求手动翻页打印背面
		"@PJL SET JOBATTR=\"@LUNA=%s\"\n"//user_name
		"@PJL SET COPIES=%d\n"//copyies 复制份数
		"@PJL SET QTY=%d\n"//qty 任务数量
		"@PJL SET JOBATTR=\"@TRCH=OFF\"\n"
		"@PJL SET DUPLEX=%s\n"//双页：ON 单页：OFF
		"@PJL SET BINDING=%s\n"//装订边 长边：LONGEDGE 短边：SHORTEDGE
		"%s"//Render Model
		"@PJL SET ECONOMODE=%s\n"//draft 草稿模式：ON/OFF
		"@PJL SET RET=ON\n"
		"@PJL SET JOBATTR=\"@IREC=OFF\"\n"
		"@PJL SET JOBATTR=\"@NLPP=%s\"\n"//打印质量 注：other_quality其他质量:N2 多合一选项 1in1：1  2in1：N2  4in1：N4  8in1：N8  16in1：N16  32in1：N32
		"@PJL SET JOBATTR=%s\n"//双页："@HOAD=IC0A8016B" 单页："@HOAD=IC0A80169"
		"@PJL SET JOBATTR=\"@JOAU=%s\"\n"//user_name
		"@PJL SET JOBATTR=\"@CNAM=%s\"\n"//host_name
		"@PJL SET IWAMANUALDUP=%s\n"//手动双页：ON 单页：OFF
		"@PJL SET IWAJAMRECOVERY=AUTO\n"
		"@PJL SET JOBATTR=\"@MSIP=%s\"\n"//paper media type 纸张类型
		"@PJL SET PAPERDIRECTION=SEF\n"
		"@PJL SET JOBATTR=\"@PSMD=OFF\"\n"
		"@PJL SET RESOLUTION=%d\n"//分辨率 pix/inch
		"@PJL SET BITSPERPIXEL=8\n"//单像素数据占位数
		"@PJL SET JOBATTR=\"@DRDM=RASTER\"\n"
		"%s"//Render Quality 打印质量
		"@PJL ENTER LANGUAGE=HBPL\n";

static char head_tail_template[12] = {
	'A',
	0x81, 0xa1, 0x00,
	0x82, 0xa2, 0x07, 0x00,
	0x83, 0xa2, 0x01, 0x00
};

char* get_hbpl_head(char *date , char *time, char *user, char *host,
		char *file_name, int num_page, bool color, int duplex, int media, int w,
		int h, int paper, int copies, int resolution, int quality, bool draft,
		int nlpp);


//duplex_model: 0-no_duplex  1-duplex_back 2-duplex_front
//resoultion:300 , 600 , 1200 dpi
char *set_hbpl_page_head(char *page,paper_type paper,int width,int height,int resoultion,int page_index,unsigned char duplex_model);
#endif /* HBPLV1_TEMPLATE_H_ */

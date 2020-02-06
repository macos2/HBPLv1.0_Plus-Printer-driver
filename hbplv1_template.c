/*
 * hbplv1_template.c
 *
 *  Created on: 2020年1月30日
 *      Author: tom
 *      https://github.com/macos2
 *      https://gitee.com/macos2
 */


#include "hbplv1_template.h"



char page_head_template_1[90]= {
	'C' ,
	0x91 , 0xa1 , 0x00 ,
	0x92 , 0xa1 , 0x01 ,
	0x93 , 0xa1 , 0x01 ,
	0x94 , 0xa1 ,
	0x00 ,//[12]paper type code like letter:0 legal:2 a4:4 executive:6 ....
	0x95 , 0xc2 ,
	0x00 , 0x00 , 0x00 , 0x00 ,//[15][17] custom pagesize wxh in  0.1mm unit，自定义纸张 wxh 单位0.1mm 例：200mm={0xd0,0x07}=0x07d0=2000x0.1mm
	0x96 , 0xa1 , 0x00 ,//[21]  custom pagesize 0x02 自定义纸张大小：0x02
	0x97 , 0xc3 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x98 , 0xa1 , 0x00 ,//not_duplex_mode:0x00,duplex_mode（front:0x02,back:0x01）,非双面打印：0x00,双面打印（正面：0x02，背面：0x01）
	0x99 , 0xa4 ,
	0x00 , 0x00 , 0x00 , 0x00 ,//[33] page index like 1,2,3
	0x9a , 0xc4 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,//[39][43]WxH 图像大小WxH，非纸张大小
	0x9b , 0xa1 , 0x00 ,//[46]under duplex model,0x01 mean haven't manual flip, 0x00 mean have manual flip.双面打印，0x01 没翻页，0x00已翻页
	0x9c , 0xa1 , 0x01 ,
	0x9d , 0xa1 , 0x09 ,//[55]image_color_type grayscale:0x09 color:0x8B,not print model 图像色彩类型：灰阶：0x09，彩色：0x8B 注：非打印模式
	0x9e , 0xa1 , 0x02 ,
	0x9f , 0xa1 , 0x05 ,
	0xa0 , 0xa1 , 0x08 ,
	0xa1 , 0xa1 , 0x00 ,
	0xa2 , 0xc4 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,//[70][74]WxH 图像大小WxH，非纸张大小
	'Q'  ,  'R' ,
	0xa3 , 0xa1 , 0x00 ,
	0xa4 , 0xb1 ,
	0xa2 ,//[85]page_data_length>0xffff? 0xa2 : 0xa4
	0x00,0x00,0x00,0x00,//page_data_length
};

//page_data_length between page_head_template_1 and page_head_template_2

char page_head_template_2[52]={
	0x20 , 0x00 , 0x00 , 0x00 ,
	0x00 , //[4] grayscale:0x08 color:0x00
	0x01 ,
	0x00 , //[6] grayscale:0x00 color:0x01
	0x00 ,
	0x10 , 0x32 , 0x04 , 0x00 ,
	0xa1 , 0x42 , 0x00 , 0x00 , 0x00 , 0x00 , 0xff ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,0x00, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,//preserve blank 预留空间
	0x00 , 0x00 , 0x00 , 0x00 ,//color data length
	0x00 , 0x00 , 0x00 , 0x00 ,//color data length
	0x00 , 0x00 , 0x00 , 0x00 ,//color data length
	0x00 , 0x00 , 0x00 , 0x00 ,//color data length
};


char *get_hbpl_head(char *date,char *time,char *user,char *host,char *file_name,int num_page,bool color,int duplex,int media,int w,int h,int paper,int copies,int resolution,int quality,bool draft,int nlpp){
	char *info=NULL;
	char *s_iwside2start=NULL,*s_binding=S_LONGEDGE;
	char *s_quality;
	int temp;
	size_t s=0;
	switch (duplex){
	case duplex_manual_longedge:
		asprintf(&s_iwside2start,iwside2start,(num_page+num_page%2)/2+(num_page+1)%2);
		break;
	case duplex_manual_shortedge:
		s_binding=S_SHORTEDGE;
		asprintf(&s_iwside2start,iwside2start,(num_page+num_page%2)/2+(num_page+1)%2);
		break;
	default:
		asprintf(&s_iwside2start,"");
		break;
	}

	if(color){
		switch (quality) {
			case print_quality_gradation:
				s_quality=color_gradation;
				break;
			case print_quality_fineness:
				s_quality=color_fineness;
				break;
			case print_quality_standard:
				s_quality=color_standard;
				break;
			case print_quality_normal:
			default:
				s_quality=color_normal;
				break;
		}
	}else{
		switch (quality) {
			case print_quality_gradation:
				s_quality=grayscale_gradation;
				break;
			case print_quality_fineness:
				s_quality=grayscale_fineness;
				break;
			case print_quality_standard:
				s_quality=grayscale_standard;
				break;
			case print_quality_normal:
			default:
				s_quality=grayscale_normal;
				break;
		}
	}

	s=asprintf(&info,head_template,\
			date,\
			time,\
			file_name,\
			s_iwside2start,\
			user,\
			copies,\
			1,\
			duplex!=duplex_off?S_ON:S_OFF,\
			s_binding,\
			color==true?render_model_color:render_model_grayscale,\
			draft==true?S_ON:S_OFF,\
			n_in_page_name[nlpp],\
			"\"@HOAD=IC0A80169\"\0",\
			user,\
			host,\
			duplex!=duplex_off?S_ON:S_OFF,\
			media_type_name[media],\
			resolution,\
			s_quality
			);
	if(s_iwside2start!=NULL)free(s_iwside2start);
	return info;
};


char *set_hbpl_page_head(char *page,paper_type paper,int width,int height,int resoultion,int page_index,unsigned char duplex_model){
	int paper_w,paper_h;
	char *head=page;
	head[12]=paper_type_code[paper];
	if(paper==paper_custom){
		//	setle (head+15, 2,  (width*254+300)/600);  // units of 0.1mm
		//	setle (head+17, 2, (height*254+300)/600);
		paper_w=width*254/resoultion;
		paper_h=height*254/resoultion;
		head[15]=(char)paper_w&0xff;
		head[16]=(char)(paper_w>>8)&0xff;
		head[17]=(char)paper_h&0xff;
		head[18]=(char)(paper_h>>8)&0xff;
	}
	head[33]=page_index;
	head[30]=duplex_model;
	if(duplex_model==2)//duplex front
		head[46]=0x01;
	return head;
};


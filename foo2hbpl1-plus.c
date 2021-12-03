/*
 * foo2hbpl1-plus.c
 *
 *  Created on: 2020年1月28日
 *      Author: tom
 *      https://github.com/macos2
 *      https://gitee.com/macos2
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include "hbplv1_template.h"
#include "hbplv1_encode.h"
char host_name[256];
char user_name[256];
char file_name[256];
char _date[16];
char _time[16];
time_t t;
int rand_job_num;
bool color = false, draft = false,quit=false;
unsigned char duplex = 0, media = 0, paper = 0, quality = 0, nlpp = nlpp_n1;
unsigned int resolution = 600, copies = 1;
unsigned int paper_size_w = 0., paper_size_h = 0.; //mm

static char *short_opt = "c:d:m:g:p:n:r:q:t:J:U:l:";
struct option long_opt[] = { { "color", 1, NULL, 'c' },
		{ "duplex", 1, NULL, 'd' }, { "media", 1, NULL, 'm' }, { "papersize", 1,
				NULL, 'g' }, { "paper", 1, NULL, 'p' },
		{ "copies", 1, NULL, 'n' }, { "resolution", 1, NULL, 'r' }, { "quality",
				1, NULL, 'q' }, { "draft", 1, NULL, 't' }, { "filename", 1,
				NULL, 'J' }, { "username", 1, NULL, 'U' }, { "n_in_page", 1,
				NULL, 'l' }, };

void print_help(int argc,char *argv[]){
	printf("Usage %s [Option] [-J file] >output\n"
			"Option:\n\t"
			"*:the default value if not special or invaild param\n\t"
			"-c|--color=\t*0:Grayscale | 1:Color\n\t"
			"-d|--duplex=\t*0:duplex off | 1:manual duplex longedge | 2:manual duplex shortedge\n\t"
			"-m|--media=\t*0:unknow 1:plain 2:bond 3:lwcard 4:labels 5:envelope 6:recycled 7:plain2 8:bond2 9:lwcard2 10:lwgard2 11:recycled2\n\t"
			"-g|--papersize= \t width x height, mm unit\n\t"
			"-p|--paper=\t*0:Letter 1:Legal 2:A4 3:Executive 4:Envelope10 5:Monarch-Envelope 6:A5 7:C5-Envelope 8:DL-Envelope 9:B5-ISO 10:B5-JIS 11:Folio\n\t\t\t12:Custom(if not special -g params,it will calculate with the resoultion and image WxH)\n\t"
			"-n|--copies=\tnumber of copies\n\t"
			"-r|--resoultion=\t300 | *600 | 1200\n\t"
			"-q|--quality=\t0:normal | 1:standard | 2:fineness | 3:gradation\n\t"
			"-t|--draft=\t*0:draft off | 1:draft on\n\t"
			"-J|--filename=\tfilename for input ,or stdin as default if not special\n\t"
			"-U|--username=\tspecial username\n\t"
			"-l|--n_in_page=\t0:1in1 | 1:2in1 | 2:4in1 | 3:8in1 | 4:16in1 | 5:32in1\n\t"
			,argv[0]);
}

void init_global() {

	memset(&host_name, 0, 256);
	memset(&user_name, 0, 256);
	memset(&file_name, 0, 256);
	memset(&_date, 0, 16);
	memset(&_time, 0, 16);

	t = time(NULL);
	srand(t);
	rand_job_num=rand();
	strftime(_time, 16, "%H:%M:%S", localtime(&t));
	strftime(_date, 16, "%m/%d/%Y", localtime(&t));

	gethostname(&host_name, 256);
	char *user=getlogin();
	if(user!=NULL)
	strncpy(user_name, user, sizeof(user));
}

void parse_arg(int argc, char *argv[]) {
	int opt = 0;
	while ((opt = getopt_long(argc, argv, short_opt, long_opt, NULL)) !=  EOF) {
		switch (opt) {
		case 'c':
			color = atoi(optarg);
			break;
		case 'd':
			duplex = atoi(optarg);
			if (duplex < 0 || duplex > 2)
				duplex = 0;
			break;
		case 'm':
			media = atoi(optarg);
			if (media < 0 || media > 11)
				media = 0;
			break;
		case 'g':
			sscanf(optarg, "%dx%d", &paper_size_w, &paper_size_h);
			break;
		case 'p':
			paper = atoi(optarg);
			if (paper > 12)
				paper = 0;
			break;
		case 'n':
			copies = atoi(optarg);
			if (copies <= 0)
				copies = 1;
			break;
		case 'r':
			resolution = atoi(optarg);
			if (resolution != 300 && resolution != 600 && resolution != 1200)
				resolution = 600;
			break;
		case 'q':
			quality = atoi(optarg);
			if (quality < 0 || quality > 3)
				quality = 0;
			break;
		case 't':
			draft = atoi(optarg);
			break;
		case 'J':
			strncpy(file_name, optarg, 256);
			break;
		case 'U':
			strncpy(user_name, optarg, 256);
			break;
		case 'l':
			nlpp = atoi(optarg);
			if (nlpp > 5)
				nlpp = nlpp_n1;
			break;
		default:
			print_help(argc,argv);
			quit=true;
			return;
			break;
		}
	}
//	if(paper==paper_custom&&paper_size_w==0&&paper_size_h==0){
//		paper_size_w=76.2*resolution/25.4;
//		paper_size_h=127*resolution/25.4;
//	}
//		printf("-c %s\n-d %d\n-m %d\n-g %dx%d\n-p %d\n-n %d\n-r %d\n-q %d\n-t %s\n-J %s\n-U %s\n",color?"true":"false",duplex,media,paper_size_w,paper_size_h,paper,copies,resolution,quality,draft?"true":"false",file_name,user_name);
}

int hbpl_print(const FILE *file) {
	int i = 0,d=0,p=0;
	unsigned char duplex_dir=2;
	char *head1, *head2,rand_job_num_str[9];
	size_t num_page=0,num_page_limt=0;
	page_data **page_set=NULL;
	//JOB START
	sprintf(rand_job_num_str,"%0X",rand_job_num);
	printf("%s",job_start_head);
	printf("%s",rand_job_num_str);
	printf("%s",job_start_tail);
	fflush(stdout);
	//JOB HEAD
	hbplv1_do_file(file,&num_page,&num_page_limt,&page_set);//Parse input data to generate the job head
	if(duplex!=duplex_off&&num_page==1){//turn off the duplex mode when printing only 1 page.
		duplex=duplex_off;
	}
	char *head = get_hbpl_head(_date, _time, user_name, host_name, file_name,
			num_page, color, duplex, media, paper_size_w, paper_size_h, paper,
			copies, resolution, quality, draft, nlpp);
	printf("%s", head);
	fwrite(head_tail_template, 12, 1,stdout);
	fflush(stdout);
	//PAGES DATA
	if (duplex != duplex_off) {
		i = num_page % 2;//skip first page when odd pages output under duplex model.
		d=num_page+num_page%2;
		while (i < d) {
			if(i>=((num_page+num_page%2)/2))duplex_dir=1;
			if(duplex_dir==2){
				//print front side,page order example: 6,4,2; 打印前面，打印顺序6，4，2
				p=d-2*i;
			}else{
				//print back side,page order example: 1,3,5;打印背面，打印顺序1,3,5
				p=2*i+1-d;
			}
			p--;
			set_hbpl_page_head(page_set[p]->image, paper, page_set[p]->width,
					page_set[p]->height, resolution, i, duplex_dir);
			fwrite(page_set[p]->image, page_set[p]->len, 1, stdout);
			fflush(stdout);
			free(page_set[p]->image);
			free(page_set[p]);
			i++;
		}
	} else {
		for (i = 0; i < num_page; i++) {
			set_hbpl_page_head(page_set[i]->image, paper, page_set[i]->width,
					page_set[i]->height, resolution, i, false);
			fwrite(page_set[i]->image, page_set[i]->len, 1, stdout);
			fflush(stdout);
			free(page_set[i]->image);
			free(page_set[i]);
		}
	}
	//JOB END
	printf("B%s",job_end_head);
	printf("%s",rand_job_num_str);
	printf("%s",job_end_tail);
	fflush(stdout);
	free(head);
	return 0;
}

int main(int argc, char *argv[]) {
	init_global();
	parse_arg(argc, argv);
	if(quit)return 0;
	FILE *in;
	if (strcmp(file_name, "") == 0) {
		in = stdin;
	} else {
		in = fopen(file_name, "r");
		if (in == NULL) {
			perror("File cannot read.");
			return -1;
		}
	}

	hbpl_print(in);
	fclose(in);
	return 0;
}

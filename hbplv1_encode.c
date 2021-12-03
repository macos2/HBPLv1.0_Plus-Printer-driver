/*
 * hbplv1_encode.c
 *
 *  Created on: 2020年2月2日
 *      Author: tom
 *      https://github.com/macos2
 *      https://gitee.com/macos2
 */

#include "hbplv1_encode.h"

//void
//error(int fatal, char *fmt, ...)
//{
//    va_list ap;
//
//    va_start(ap, fmt);
//    vfprintf(stderr, fmt, ap);
//    va_end(ap);
//
//    if (fatal) exit(fatal);
//}

struct stream {
	unsigned char *buf;
	int size, off, bits;
};

void putbits(struct stream *s, unsigned val, int nbits) {
	if (s->off + 16 > s->size
			&& !(s->buf = realloc(s->buf, s->size += 0x100000)))
//	    error (1, "Out of memory\n");
		perror("Out of memory\n");
	if (s->bits) {
		s->off--;
		val |= s->buf[s->off] >> (8 - s->bits) << nbits;
		nbits += s->bits;
	}
	s->bits = nbits & 7;
	while ((nbits -= 8) > 0)
		s->buf[s->off++] = val >> nbits;
	s->buf[s->off++] = val << -nbits;
}

/*
 Runlengths are integers between 1 and 17057 encoded as follows:

 1	00
 2	01 0
 3	01 1
 4	100 0
 5	100 1
 6	101 00
 7	101 01
 8	101 10
 9	101 11
 10	110 0000
 11	110 0001
 12	110 0010
 ...
 25	110 1111
 26	111 000 000
 27	111 000 001
 28	111 000 010
 29	111 000 011
 ...
 33	111 000 111
 34	111 001 000
 ...
 41	111 001 111
 42	111 010 000
 50	111 011 0000
 66	111 100 00000
 98	111 101 000000
 162	111 110 000000000
 674	111 111 00000000000000
 17057	111 111 11111111111111
 */
void put_len(struct stream *s, unsigned val) {
	unsigned code[] = { 1, 0, 2, 2, 2, 3, 4, 8, 4, 6, 0x14, 5, 10, 0x60, 7, 26,
			0x1c0, 9, 50, 0x3b0, 10, 66, 0x780, 11, 98, 0xf40, 12, 162, 0x7c00,
			15, 674, 0xfc000, 20, 17058 };
	int c = 0;

	if (val < 1 || val > 17057)
		return;
	while (val >= code[c + 3])
		c += 3;
	putbits(s, val - code[c] + code[c + 1], code[c + 2]);
}

/*
 CMYK byte differences are encoded as follows:

 0	000
 +1	001
 -1	010
 2	011s0	s = 0 for +, 1 for -
 3	011s1
 4	100s00
 5	100s01
 6	100s10
 7	100s11
 8	101s000
 9	101s001
 ...
 14	101s110
 15	101s111
 16	110s00000
 17	110s00001
 18	110s00010
 ...
 46	110s11110
 47	110s11111
 48	1110s00000
 49	1110s00001
 ...
 78	1110s11110
 79	1110s11111
 80	1111s000000
 81	1111s000001
 ...
 126	1111s101110
 127	1111s101111
 128	11111110000
 */
void put_diff(struct stream *s, signed char val) {
	static unsigned short code[] = { 2, 3, 3, 1, 4, 4, 3, 2, 8, 5, 3, 3, 16, 6,
			3, 5, 48, 14, 4, 5, 80, 15, 4, 6, 129 };
	int sign, abs, c = 0;

	switch (val) {
	case 0:
		putbits(s, 0, 3);
		return;
	case 1:
		putbits(s, 1, 3);
		return;
	case -1:
		putbits(s, 2, 3);
		return;
	}
	abs = ((sign = val < 0)) ? -val : val;
	while (abs >= code[c + 4])
		c += 4;
	putbits(s, code[c + 1], code[c + 2]);
	putbits(s, sign, 1);
	putbits(s, abs - code[c], code[c + 3]);
}

void setle(unsigned char *c, int s, int i) {
	while (s--) {
		*c++ = i;
		i >>= 8;
	}
}

int getint(FILE *fp) {
	int c, ret;

	for (;;) {
		while (isspace(c = fgetc(fp)))
			;
		if (c == '#')
			while (fgetc(fp) != '\n')
				;
		else
			break;
	}
	if (!isdigit(c))
		return -1;
	for (ret = c - '0'; isdigit(c = fgetc(fp));)
		ret = ret * 10 + c - '0';
	return ret;
}

int hbplv1_do_file(FILE *fp,size_t *num_of_page,size_t *num_of_page_limt,page_data ***set_of_page) {
	int type, iwide, ihigh, ideep, imax, ibyte;
	int wide, deep, byte, row, col, i, k;
	char tupl[128], line[128];
	unsigned char *image, *sp, *dp;

	size_t num_page=0,num_page_limt=0;
	page_data **page_set=NULL;

	while ((type = fgetc(fp)) != EOF) {
		type = ((type - 'P') << 8) | fgetc(fp);
		tupl[0] = iwide = ihigh = ideep = deep = imax = ibyte = -1;
		switch (type) {
		case '4':
			deep = 1 + (ideep = 0);
			goto six;
		case '5':
			deep = ideep = 1;
			goto six;
		case '6':
			deep = 1 + (ideep = 3);
			six: iwide = getint(fp);
			ihigh = getint(fp);
			imax = type == '4' ? 255 : getint(fp);
			break;
		case '7':
			do {
				if (!fgets(line, 128, fp))
					goto fail;
				if (!strncmp(line, "WIDTH ", 6))
					iwide = atoi(line + 6);
				if (!strncmp(line, "HEIGHT ", 7))
					ihigh = atoi(line + 7);
				if (!strncmp(line, "DEPTH ", 6))
					deep = ideep = atoi(line + 6);
				if (!strncmp(line, "MAXVAL ", 7))
					imax = atoi(line + 7);
				if (!strncmp(line, "TUPLTYPE ", 9))
					strcpy(tupl, line + 9);
			} while (strcmp(line, "ENDHDR\n"));
			if (ideep != 4 || strcmp(tupl, "CMYK\n"))
				goto fail;
			break;
		default:
			goto fail;
		}
		if (iwide <= 0 || ihigh <= 0 || imax != 255)
			goto fail;
		wide = -(-iwide & -8);
		if (ideep)
			ibyte = iwide * ideep;
		else
			ibyte = wide >> 3;
		byte = wide * deep;
		image = calloc(ihigh + 2, byte);
		for (row = 1; row <= ihigh; row++) {
			i = fread(image, ibyte, 1, fp);
			sp = image;
			dp = image + row * byte;
			for (col = 0; col < iwide; col++) {
				dp += deep;
				switch (ideep) {
				case 0:
					*dp = ((image[col >> 3] >> (~col & 7)) & 1) * 255;
					break;
				case 1:
					*dp = ~*sp;
					break;
				case 3:
					for (k = sp[2], i = 0; i < 2; i++)
						if (k < sp[i])
							k = sp[i];
					*dp = ~k;
					for (i = 0; i < 3; i++)
						dp[i + 1] = k ? (k - sp[i]) * 255 / k : 255;
					break;
				case 4:
					for (i = 0; i < 4; i++)
						dp[i] = sp[((i - 1) & 3)];
					break;
				}
				sp += ideep;
			}
			for (i = 0; i < deep * Clip[0]; i++)
				image[row * byte + deep + i] = 0;
			for (i = deep * (iwide - Clip[2]); i < byte; i++)
				image[row * byte + deep + i] = 0;
		}
		memset(image + deep, 0, byte * (Clip[1] + 1));
		memset(image + deep + byte * (ihigh - Clip[3] + 1), 0, byte * Clip[3]);

		if (page_set == NULL) {
			page_set = malloc(getpagesize());
			num_page_limt = getpagesize() / sizeof(char*);
		}
		if ((num_page + 1) > num_page_limt) {
			page_set = realloc(page_set,
					num_page_limt * sizeof(char*) + getpagesize());
			num_page_limt += getpagesize() / sizeof(char*);
		}

		page_set[num_page] = hbplv1_encode_page(deep>1,iwide,ihigh,image);
		num_page++;
		//hbplv1_encode_page(deep > 1, iwide, ihigh, (char *) image);
		free(image);
	}
	//output result
	if(num_of_page!=NULL)*num_of_page=num_page;
	if(num_of_page_limt!=NULL)*num_of_page_limt=num_page_limt;
	if(set_of_page!=NULL)*set_of_page=page_set;

	return 0;
	fail: fprintf(stderr, "Not an acceptable PBM, PPM or PAM file!!!\n");
	return -1;
}

#define IP (((int *)image) + off)
#define CP (((char *)image) + off)
#define DP (((char *)image) + off*deep)
#define BP(x) ((blank[(off+x) >> 3] << ((off+x) & 7)) & 128)
#define put_token(s,x) putbits(s, huff[hsel][x] >> 4, huff[hsel][x] & 15)

page_data* hbplv1_encode_page(int color, int width, int height, char *image) {
	page_data *output = NULL;
	size_t output_size;
	unsigned char head[90]=
    {
	0x43,0x91,0xa1,0x00,0x92,0xa1,0x01,0x93,0xa1,0x01,0x94,0xa1,
	0x00,0x95,0xc2,0x00,0x00,0x00,0x00,0x96,0xa1,0x00,0x97,0xc3,
	0x00,0x00,0x00,0x00,0x98,0xa1,0x00,0x99,0xa4,0x01,0x00,0x00,
	0x00,0x9a,0xc4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9b,
	0xa1,0x00,0x9c,0xa1,0x01,0x9d,0xa1,0x00,0x9e,0xa1,0x02,0x9f,
	0xa1,0x05,0xa0,0xa1,0x08,0xa1,0xa1,0x00,0xa2,0xc4,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x51,0x52,0xa3,0xa1,0x00,0xa4,
	0xb1,0xa4
    };
	unsigned char body[52] =
    {
	0x20,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x32,0x04,0x00,
	0xa1,0x42,0x00,0x00,0x00,0x00,0xff
    };
//    static short papers[] =
//    {	// Official sizes to nearest 1/600 inch
//	// will accept +-1.5mm (35/600 inch) tolerance
//	  0, 5100, 6600,	// Letter
//	  2, 5100, 8400,	// Legal
//	  4, 4961, 7016,	// A4
//	  6, 4350, 6300,	// Executive
//	 13, 2475, 5700,	// #10 envelope
//	 15, 2325, 4500,	// Monarch envelope
//	 17, 3827, 5409,	// C5 envelope
//	 19, 2599, 5197,	// DL envelope
////	 ??, 4158, 5906,	// B5 ISO
//	 22, 4299, 6071,	// B5 JIS
//	 30, 3496, 4961,	// A5
//	410, 5100, 7800,	// Folio
//    };
	static const unsigned short huff[2][8] = { { 0x01, 0x63, 0x1c5, 0x1d5,
			0x1e5, 0x22, 0x3e6 }, // for text & graphics
			{ 0x22, 0x63, 0x1c5, 0x1d5, 0x1e5, 0x01, 0x3e6 }, // for images
			};
	unsigned char *blank;
//    static int pagenum = 0;
	struct stream stream[5] = { { 0 } };
	int dirs[] = { -1, 0, -1, 1, 2 }, rotor[] = { 0, 1, 2, 3, 4 };
	int i, j, row, col, deep, dir, run, try, bdir, brun, total;
	int hsel = 0, off = 0, bit = 0, stat = 0;
//    int paper = 510;

	int margin = width - 96;

//    for (i = 0; i < sizeof papers / sizeof *papers; i++)
//	if (abs(width-papers[i+1]) < 36 && abs(height-papers[i+2]) < 36)
//	    paper = papers[i];

//	if (!MediaCode)
//		MediaCode = paper & 1 ? 6 : 1;
//    if (!pagenum)
//	start_doc(color);
//    head[12] = paper >> 1;
//    if (paper == 510)
//    {
//	setle (head+15, 2,  (width*254+300)/600);  // units of 0.1mm
//	setle (head+17, 2, (height*254+300)/600);
//	head[21] = 2;
//    }
	width = -(-width & -8);
//    setle (head+33, 4, ++pagenum);
	setle(head + 39, 4, width);
	setle(head + 43, 4, height);
	setle(head + 70, 4, width);
	setle(head + 74, 4, height);
	head[55] = 9 + color * 130;
	if (color)
		body[6] = 1;
	else
		body[4] = 8;

	deep = 1 + color * 3;
	for (i = 1; i < 5; i++)
		dirs[i] -= width;
	if (!color)
		dirs[4] = -8;

	blank = calloc(height + 2, width / 8);
	memset(blank++, -color, width / 8 + 1);
	for (row = 1; row <= height; row++) {
		for (col = deep; col < deep * 2; col++)
			image[row * width * deep + col] = -1;
		for (col = 8; col < width * deep; col += 4)
			if (*(int*) (image + row * width * deep + col)) {
				for (col = 12; col < margin / 8; col++)
					blank[row * (width / 8) + col] = -1;
				blank[row * (width / 8) + col] = -2 << (~margin & 7);
				break;
			}
	}
	memset(image, -color, (width + 1) * deep);
	image += (width + 1) * deep;
	blank += width / 8;

	while (off < width * height) {
		for (bdir = brun = dir = 0; dir < 5; dir++) {
			try = dirs[rotor[dir]];
			for (run = 0; run < 17057; run++, try++) {
				if (color) {
					if (IP[run] != IP[try])
						break;
				} else if (CP[run] != CP[try])
					break;

				if (BP(run) != BP(try))
					break;
			}
			if (run > brun) {
				bdir = dir;
				brun = run;
			}
		}
		if (brun == 0) {
			put_token(stream, 5);
			for (i = 0; i < deep; i++)
				put_diff(stream + 1 + i, DP[i] - DP[i - deep]);
			bit = 0;
			off++;
			stat--;
			continue;
		}
		if (brun > width * height - off)
			brun = width * height - off;
		if (bdir) {
			j = rotor[bdir];
			for (i = bdir; i; i--)
				rotor[i] = rotor[i - 1];
			rotor[0] = j;
		}
		if ((off - 1 + brun) / width != (off - 1) / width) {
			if (abs(stat) > 8 && ((stat >> 31) & 1) != hsel) {
				hsel ^= 1;
				put_token(stream, 6);
			}
			stat = 0;
		}
		stat += bdir == bit;
		put_token(stream, bdir - bit);
		put_len(stream, brun);
		bit = brun < 17057;
		off += brun;
	}

	putbits(stream, 0xff, 8);
	for (total = 48, i = 0; i <= deep; i++) {
		putbits(stream + i, 0xff, 8);
		stream[i].off--;
		setle(body + 32 + i * 4, 4, stream[i].off);
		total += stream[i].off;
	}
	head[85] = 0xa2 + (total > 0xffff) * 2;
	setle(head + 86, 4, total);

	output = malloc(sizeof(page_data));
	output_size=0;
	output_size += 88 + (total > 0xffff) * 2;
	output_size += 48;
	for (i = 0; i <=deep; i++) {
		output_size += stream[i].off;
	}
	output_size += 2;
	output->image = malloc(output_size);
	output->len = output_size;
	output->width = width;
	output->height = height;

	memcpy(output->image, head, 88 + (total > 0xffff) * 2);
	output_size = 88 + (total > 0xffff) * 2;
	memcpy(output->image + output_size, body, 48);
	output_size += 48;
	for (i = 0; i <= deep; i++) {
		memcpy(output->image + output_size, stream[i].buf,
				stream[i].off);
		 output_size +=stream[i].off;
		free(stream[i].buf);
	}
	memcpy(output->image + output_size, "SD", 2);
//    fwrite(head, 1, 88+(total > 0xffff)*2, stdout);
//    fwrite(body, 1, 48, stdout);
//    for (i = 0; i <= deep; i++)
//    {
//	fwrite(stream[i].buf, 1, stream[i].off, stdout);
//	free(stream[i].buf);
//    }

	free(blank - width / 8 - 1);
	return output;
}
#undef IP
#undef CP
#undef DP
#undef BP
#undef put_token

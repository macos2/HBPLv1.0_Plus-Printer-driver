/*
 * hbplv1_enum.h
 *
 *  Created on: 2020年1月29日
 *      Author: tom
 *      https://github.com/macos2
 *      https://gitee.com/macos2
 *      the core encode program is writed by Dave Coffin: http://www.dechifro.org/hbpl
 */

#ifndef HBPLV1_ENUM_H_
#define HBPLV1_ENUM_H_

typedef enum {
	paper_letter,
	paper_legal,
	paper_a4,
	paper_executive,
	paper_envelope10,
	paper_monarch_envelope,
	paper_a5,
	paper_c5_envelope,
	paper_dl_envelope,
	paper_b5_iso,
	paper_b5_jis,
	paper_folio,
	paper_custom,
}paper_type;

static char *paper_type_code[]={
			0x00,//paper_letter
			0x01,//paper_legal
			0x02,//paper_a4
			0x03,//paper_executive
			0x06,//paper_envelope10
			0x07,//paper_monarch_envelope
			0x0f,//paper_a5
			0x08,//paper_c5_envelope
			0x09,//paper_dl_envelope
			0x0b,//paper_b5_iso
			0x0b,//paper_b5_jis
			0xcd,//paper_folio
			0xff,//paper_custom
};

typedef enum{
duplex_off,
duplex_manual_longedge,
duplex_manual_shortedge,
}duplex_type;

typedef enum{
	media_unknow,
	media_plain,
	media_bond,
	media_lwcard,
	media_labels,
	media_envelope,
	media_recycled,
	media_plain2,
	media_bond2,
	media_lwcard2,
	media_lwgcard2,
	media_recycled2,
}media_type;

static char *media_type_name[] = { "NORMAL", "NORMAL", "THICK", "HIGHQUALITY",
		"COAT2", "LABEL", "ENVELOPE", "RECYCLED", "NORMALREV", "THICKSIDE2",
		"HIGHQUALITYREV", "COATEDPAPER2REV", "RECYCLEREV" };

typedef enum {
	print_quality_normal,
	print_quality_standard,
	print_quality_fineness,
	print_quality_gradation,
}print_quality;

typedef enum{
	nlpp_n1,
	nlpp_n2,
	nlpp_n4,
	nlpp_n8,
	nlpp_n16,
	nlpp_n32,
}n_in_page;

static char *n_in_page_name[] = { "1", "N2", "N4", "N8", "N16", "N32" };

#endif /* HBPLV1_ENUM_H_ */

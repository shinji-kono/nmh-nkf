/* ml_codeconv.c - (multilingual) code conversion */
/*			by takada@seraph.ntt.jp   */
/*			arranged by MH-plus project */

#include <h/mh.h>
#include <h/mhparse.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

static void ml_conv_sbr();

/* NKF Input/Output pointers */

static unsigned char *nkf_output;
static unsigned char *nkf_input;
static int nkf_input_ctr;
static int nkf_output_ctr;
static int nkf_limit;
static int nkf_ilimit;
static void (*nkf_flush)(unsigned char *,int);

static void nkf_open(unsigned char *opt, unsigned char *in,int ilimit,
	unsigned char *out,int limit,void (*flush)(unsigned char *,int),FILE *fp);
static void nkf_continue(unsigned char *in,int ilimit) ;
static void nkf_end() ;
static void none(unsigned char *a,int b);

static void extend(unsigned char *out,int out_count);

static FILE *nkf_file;

char *
ml_conv_decode(s,encode,charset)
     char *s;
     int encode,charset;
{
    ml_conv_sbr(s, encode, charset);
    return(s);
}

static char *
cs_input_opt(int encode, int input_charset)
{
    switch(encode) {
    case CE_BASE64: 
        return "-dwmBW8";
    case CE_QUOTED: 
        return "-wmQW8";
    }
    return "-wW8";
} 

static void
ml_conv_sbr(in, encode, input_charset)
     char *in;
     int encode, input_charset;
{
    char *opt = cs_input_opt(encode,input_charset);
    int len = strlen(in);
    char *buf = alloca(len+1);
    strcpy(buf,in);
    nkf_open((unsigned char *)opt,(unsigned char *)buf,len,(unsigned char *)in,len,extend,0);
    nkf_end();
    nkf_output[nkf_output_ctr]=0;
}

#undef CR
#undef LIMIT
#undef PROTO

#undef getc
#undef ungetc

#define getc(f)   	nkf_getc()
#define ungetc(c,f)	nkf_ungetc(c)

static int
nkf_getc() {
    if (nkf_ilimit==-1) {
	int c = nkf_input[nkf_input_ctr++];
	if (c==0) {
	    nkf_input_ctr--; return -1;
	}
	return c;
    }
    return (nkf_input_ctr>=nkf_ilimit?-1:nkf_input[nkf_input_ctr++]);
}

static int
nkf_ungetc(int c) {
    nkf_input_ctr--;
    return c;
}


#undef putchar
#undef TRUE
#undef FALSE
#define putchar(c)	nkf_putchar(c)

#define debug nkf_debug

static
int
nkf_putchar(unsigned int c) 
{
    /* string length is enough? */
    if(nkf_output_ctr<nkf_limit && c!='\n') {
	return nkf_output[nkf_output_ctr++] = c;
    } else {
	nkf_output[nkf_output_ctr++] = c;
	nkf_flush(nkf_output,nkf_output_ctr);
	nkf_output_ctr = 0;
    }
    return c;
}


/* Include kanji filter main part */
/* getchar and putchar will be replaced during inclusion */

#define version  NKF_version
#define PERL_XS 1
#include "../nkf-utf8/utf8tbl.c"
#include "../nkf-utf8/nkf.c"

/*
      using opt ( "-w8" etc... )
      convert *in into *out
      when limit or nkf_end flush is called

      nkf_continue can be use to change input ptr
 */

static void
nkf_open(unsigned char *opt, unsigned char *in,int ilimit,
	unsigned char *out,int limit,void (*flush)(unsigned char *,int),FILE *fp) {
    /* Flags are reset at each call. */
    reinit();

    /* Process flags except the last once */
    options(opt);
    
    nkf_input_ctr = 0;
    nkf_input  = in;
    nkf_ilimit =  ilimit;

    nkf_file = fp;

    nkf_output_ctr = 0;
    nkf_output = out;

    nkf_limit =  limit;
    nkf_flush =  flush;

    /* Convestion */
    kanji_convert(NULL);
}

static void
nkf_continue(unsigned char *in,int ilimit) {
    nkf_input_ctr = 0;
    nkf_input  = in;
    nkf_ilimit =  ilimit;
    /* Convestion */
    kanji_convert(NULL);
}

void
nkf_end() {
    if (nkf_output_ctr) {
	nkf_flush(nkf_output,nkf_output_ctr);
	nkf_output_ctr = 0;
    }
}

static void
extend(unsigned char *out,int out_count)
{
    nkf_output += nkf_output_ctr;
}

static void
none(unsigned char *a,int b)
{
}




/* end */

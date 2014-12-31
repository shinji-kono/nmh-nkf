/*
 * mh.h -- main header file for all of nmh
 */

#include <h/nmh.h>

/*
 * Well-used constants
 */
#define	NOTOK        (-1)	/* syscall()s return this on error */
#define	OK             0	/*  ditto on success               */
#define	DONE           1	/* trinary logic                   */
#define ALL           ""
#define	Nbby           8	/* number of bits/byte */

#define MAXARGS	    4096	/* max arguments to exec                */
#define NFOLDERS    1000	/* max folder arguments on command line */
#define DMAXFOLDER     4	/* typical number of digits             */
#define MAXFOLDER   1000	/* message increment                    */

/*
 * This macro is for use by scan, for example, so that platforms with
 * a small BUFSIZ can easily allocate larger buffers.
 */
#define NMH_BUFSIZ  (BUFSIZ>=8192 ? BUFSIZ : 8192)

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
typedef unsigned char  boolean;  /* not int so we can pack in a structure */

/* If we're using gcc then give it some information about
 * functions that abort.
 */
#if __GNUC__ > 2
#define NORETURN __attribute__((__noreturn__))
#define NMH_UNUSED(i) (void) i
#else
#define NORETURN
#define NMH_UNUSED(i) i
#endif

/*
 * char array that keeps track of size in both bytes and characters
 * Usage note:
 *    Don't store return value of charstring_buffer() and use later
 *    after intervening push_back's; use charstring_buffer_copy()
 *    instead.
 */
typedef struct charstring *charstring_t;

charstring_t charstring_create (size_t);
charstring_t charstring_copy (const charstring_t);
void charstring_free (charstring_t);
/* Append a single-byte character: */
void charstring_push_back (charstring_t, const char);
/* Append possibly multi-byte character(s): */
void charstring_push_back_chars (charstring_t, const char [], size_t, size_t);
void charstring_append (charstring_t, const charstring_t);
void charstring_append_cstring (charstring_t, const char []);
void charstring_clear (charstring_t);
/* Don't store return value of charstring_buffer() and use later after
   intervening push_back's; use charstring_buffer_copy() instead. */
const char *charstring_buffer (const charstring_t);
/* User is responsible for free'ing result of buffer copy. */
char *charstring_buffer_copy (const charstring_t);
size_t charstring_bytes (const charstring_t);
size_t charstring_chars (const charstring_t);
/* Length of the last character in the charstring. */
int charstring_last_char_len (const charstring_t);

/*
 * user context/profile structure
 */
struct node {
    char *n_name;		/* key                  */
    char *n_field;		/* value                */
    char  n_context;		/* context, not profile */
    struct node *n_next;	/* next entry           */
};

/*
 * switches structure
 */
#define	AMBIGSW	 (-2)	/* from smatch() on ambiguous switch */
#define	UNKWNSW	 (-1)	/* from smatch() on unknown switch   */

struct swit {

    /*
     * Switch name
     */

    char *sw;

    /* The minchars field is apparently used like this:

       -# : Switch can be abbreviated to # characters; switch hidden in -help.
       0  : Switch can't be abbreviated;               switch shown in -help.
       #  : Switch can be abbreviated to # characters; switch shown in -help. */
    int minchars;

    /*
     * If we pick this switch, return this value from smatch
     */

    int swret;
};

/*
 * Macros to use when declaring struct swit arrays.
 *
 * These macros use a technique known as X-Macros.  In your source code you
 * use them like this:
 *
 * #define FOO_SWITCHES \
 *    X("switch1", 0, SWITCHSW) \
 *    X("switch2", 0, SWITCH2SW) \
 *    X("thirdswitch", 2, SWITCH3SW) \
 *
 * The argument to each entry in FOO_SWITCHES are the switch name (sw),
 * the minchars field (see above) and the return value for this switch.
 * Note that the last entry in the above definition must either omit the
 * continuation backslash, or be followed by a blank line.  In the nmh
 * code the style is to have every line include a backslash and follow
 * the SWITCHES macro definition by a blank line.
 *
 * After you define FOO_SWITCHES, you instantiate it as follows:
 *
 * #define X(sw, minchars, id) id,
 * DEFINE_SWITCH_ENUM(FOO);
 * #undef X
 *
 * #define X(sw, minchars, id) { sw, minchars, id },
 * DEFINE_SWITCH_ARRAY(FOO);
 * #undef X
 *
 * DEFINE_SWITCH_ENUM defines an extra enum at the end of the list called
 * LEN_FOO.
 */

#define DEFINE_SWITCH_ENUM(name) \
    enum { \
    	name ## _SWITCHES \
	LEN_ ## name \
    }

#define DEFINE_SWITCH_ARRAY(name, array) \
    static struct swit array[] = { \
    	name ## _SWITCHES \
	{ NULL, 0, 0 } \
    }

extern struct swit anoyes[];	/* standard yes/no switches */

/*
 * general folder attributes
 */
#define READONLY   (1<<0)	/* No write access to folder    */
#define	SEQMOD	   (1<<1)	/* folder's sequences modifed   */
#define	ALLOW_NEW  (1<<2)	/* allow the "new" sequence     */
#define	OTHERS	   (1<<3)	/* folder has other files	*/
#define	MODIFIED   (1<<4)	/* msh in-core folder modified  */

#define	FBITS "\020\01READONLY\02SEQMOD\03ALLOW_NEW\04OTHERS\05MODIFIED"

/*
 * first free slot for user defined sequences
 * and attributes
 */
#define	FFATTRSLOT  5

/*
 * internal messages attributes (sequences)
 */
#define EXISTS        (0)	/* exists            */
#define DELETED       (1)	/* deleted           */
#define SELECTED      (2)	/* selected for use  */
#define SELECT_EMPTY  (3)	/* "new" message     */
#define	SELECT_UNSEEN (4)	/* inc/show "unseen" */

#define	MBITS "\020\01EXISTS\02DELETED\03SELECTED\04NEW\05UNSEEN"

/*
 * type for holding the sequence set of a message
 */
typedef struct bvector *bvector_t;

bvector_t bvector_create (size_t /* initial size in bits, can be 0 */);
void bvector_copy (bvector_t, bvector_t);
void bvector_free (bvector_t);
void bvector_clear (bvector_t, size_t);
void bvector_clear_all (bvector_t);
void bvector_set (bvector_t, size_t);
unsigned int bvector_at (bvector_t, size_t);
const unsigned long *bvector_bits (bvector_t);
size_t bvector_maxsize (bvector_t);

typedef struct svector *svector_t;

svector_t svector_create (size_t);
void svector_free (svector_t);
char *svector_push_back (svector_t, char *);
char *svector_at (svector_t, size_t);
char **svector_find(svector_t, const char *);
char **svector_strs (svector_t);
size_t svector_size (svector_t);

typedef struct ivector *ivector_t;

ivector_t ivector_create (size_t);
void ivector_free (ivector_t);
int ivector_push_back (ivector_t, int);
int ivector_at (ivector_t, size_t);
int *ivector_atp (ivector_t, size_t);
size_t ivector_size (ivector_t);

/*
 * Primary structure of folder/message information
 */
struct msgs {
    int lowmsg;		/* Lowest msg number                 */
    int hghmsg;		/* Highest msg number                */
    int nummsg;		/* Actual Number of msgs             */

    int lowsel;		/* Lowest selected msg number        */
    int hghsel;		/* Highest selected msg number       */
    int numsel;		/* Number of msgs selected           */

    int curmsg;		/* Number of current msg if any      */

    int msgflags;	/* Folder attributes (READONLY, etc) */
    char *foldpath;	/* Pathname of folder                */

    /*
     * Name of sequences in this folder.
     */
    svector_t msgattrs;

    /*
     * bit flags for whether sequence
     * is public (0), or private (1)
     */
    bvector_t attrstats;

    /*
     * These represent the lowest and highest possible
     * message numbers we can put in the message status
     * area, without calling folder_realloc().
     */
    int	lowoff;
    int	hghoff;

    /*
     * This is an array of bvector_t which we allocate dynamically.
     * Each bvector_t is a set of bits flags for a particular message.
     * These bit flags represent general attributes such as
     * EXISTS, SELECTED, etc. as well as track if message is
     * in a particular sequence.
     */
    size_t num_msgstats;
    bvector_t *msgstats;	/* msg status */

    /*
     * A FILE handle containing an open filehandle for the sequence file
     * for this folder.  If non-NULL, use it when the sequence file is
     * written.
     */
    FILE *seqhandle;

    /*
     * The name of the public sequence file; required by lkfclose()
     */
    char *seqname;
};

/*
 * Amount of space to allocate for msgstats.  Allocate
 * the array to have space for messages numbered lo to hi.
 * Use MSGSTATNUM to load mp->num_msgstats first.
 */
#define MSGSTATNUM(lo, hi) ((size_t) ((hi) - (lo) + 1))
#define MSGSTATSIZE(mp) ((mp)->num_msgstats * sizeof *(mp)->msgstats)

/*
 * macros for message and sequence manipulation
 */
#define msgstat(mp,n) (mp)->msgstats[(n) - mp->lowoff]
#define clear_msg_flags(mp,msgnum)   bvector_clear_all (msgstat(mp, msgnum))
#define copy_msg_flags(mp,i,j)       bvector_copy (msgstat(mp,i), msgstat(mp,j))
#define get_msg_flags(mp,ptr,msgnum) bvector_copy (ptr, msgstat(mp, msgnum))
#define set_msg_flags(mp,ptr,msgnum) bvector_copy (msgstat(mp, msgnum), ptr)

#define does_exist(mp,msgnum)     bvector_at (msgstat(mp, msgnum), EXISTS)
#define unset_exists(mp,msgnum)   bvector_clear (msgstat(mp, msgnum), EXISTS)
#define set_exists(mp,msgnum)     bvector_set (msgstat(mp, msgnum), EXISTS)

#define is_selected(mp,msgnum)    bvector_at (msgstat(mp, msgnum), SELECTED)
#define unset_selected(mp,msgnum) bvector_clear (msgstat(mp, msgnum), SELECTED)
#define set_selected(mp,msgnum)   bvector_set (msgstat(mp, msgnum), SELECTED)

#define is_select_empty(mp,msgnum)  \
        bvector_at (msgstat(mp, msgnum), SELECT_EMPTY)
#define set_select_empty(mp,msgnum) \
        bvector_set (msgstat(mp, msgnum), SELECT_EMPTY)

#define is_unseen(mp,msgnum) \
        bvector_at (msgstat(mp, msgnum), SELECT_UNSEEN)
#define unset_unseen(mp,msgnum) \
        bvector_clear (msgstat(mp, msgnum), SELECT_UNSEEN)
#define set_unseen(mp,msgnum) \
        bvector_set (msgstat(mp, msgnum), SELECT_UNSEEN)

/* for msh only */
#define set_deleted(mp,msgnum)     bvector_set (msgstat(mp, msgnum), DELETED)

#define in_sequence(mp,seqnum,msgnum) \
        bvector_at (msgstat(mp, msgnum), FFATTRSLOT + seqnum)
#define clear_sequence(mp,seqnum,msgnum) \
        bvector_clear (msgstat(mp, msgnum), FFATTRSLOT + seqnum)
#define add_sequence(mp,seqnum,msgnum) \
        bvector_set (msgstat(mp, msgnum), FFATTRSLOT + seqnum)

#define is_seq_private(mp,seqnum) \
        bvector_at (mp->attrstats, FFATTRSLOT + seqnum)
#define make_seq_public(mp,seqnum) \
        bvector_clear (mp->attrstats, FFATTRSLOT + seqnum)
#define make_seq_private(mp,seqnum) \
        bvector_set (mp->attrstats, FFATTRSLOT + seqnum)
#define make_all_public(mp) \
        mp->attrstats = bvector_create(0); bvector_clear_all (mp->attrstats)

/*
 * macros for folder attributes
 */
#define clear_folder_flags(mp) ((mp)->msgflags = 0)

#define is_readonly(mp)     ((mp)->msgflags & READONLY)
#define set_readonly(mp)    ((mp)->msgflags |= READONLY)

#define other_files(mp)     ((mp)->msgflags & OTHERS)
#define set_other_files(mp) ((mp)->msgflags |= OTHERS)

#define	NULLMP	((struct msgs *) 0)

/*
 * m_getfld() message parsing
 */

#define NAMESZ  999		/* Limit on component name size.
				   RFC 2822 limits line lengths to
				   998 characters, so a header name
				   can be at most that long.
				   m_getfld limits header names to 2
				   less than NAMESZ, which is fine,
				   because header names must be
				   followed by a colon.	 Add one for
				   terminating NULL. */

#define LENERR  (-2)		/* Name too long error from getfld  */
#define FMTERR  (-3)		/* Message Format error             */
#define FLD      0		/* Field returned                   */
#define FLDPLUS  1		/* Field returned with more to come */
#define BODY     3		/* Body  returned with more to come */
#define FILEEOF  5		/* Reached end of input file        */

struct m_getfld_state;
typedef struct m_getfld_state *m_getfld_state_t;

/*
 * Maildrop styles
 */
#define	MS_DEFAULT	0	/* default (one msg per file) */
#define	MS_UNKNOWN	1	/* type not known yet         */
#define	MS_MBOX		2	/* Unix-style "from" lines    */
#define	MS_MMDF		3	/* string mmdlm2              */
#define	MS_MSH		4	/* whacko msh                 */

#define	NOUSE	0		/* draft being re-used */

#define TFOLDER 0		/* path() given a +folder */
#define TFILE   1		/* path() given a file    */
#define	TSUBCWF	2		/* path() given a @folder */

#define OUTPUTLINELEN	72	/* default line length for headers */

#define LINK	"@"		/* Name of link to file to which you are */
				/* replying. */

/*
 * credentials management
 */
struct nmh_creds {
    char *host;
    char *user;
    char *password;
};

typedef struct nmh_creds *nmh_creds_t;

/*
 * miscellaneous macros
 */
#define	pidXwait(pid,cp) pidstatus (pidwait (pid, NOTOK), stdout, cp)

#ifndef max
# define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
# define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef abs
# define abs(a) ((a) > 0 ? (a) : -(a))
#endif

/*
 * GLOBAL VARIABLES
 */
#define CTXMOD	0x01		/* context information modified */
#define	DBITS	"\020\01CTXMOD"
extern char ctxflags;

extern char *invo_name;		/* command invocation name         */
extern char *mypath;		/* user's $HOME                    */
extern char *defpath;		/* pathname of user's profile      */
extern char *ctxpath;		/* pathname of user's context      */
extern struct node *m_defs;	/* list of profile/context entries */

/* What style to use for generated Message-ID and Content-ID header
   fields.  The localname style is pid.time@localname, where time is
   in seconds.  The random style replaces the localname with some
   (pseudo)random bytes and uses microsecond-resolution time. */
int save_message_id_style (const char *);
char *message_id (time_t, int);

/*
 * These standard strings are defined in config.c.  They are the
 * only system-dependent parameters in nmh, and thus by redefining
 * their values and reloading the various modules, nmh will run
 * on any system.
 */
extern char *buildmimeproc;
extern char *catproc;
extern char *components;
extern char *context;
extern char *current;
extern char *credentials_file;
extern char *defaultfolder;
extern char *digestcomps;
extern char *distcomps;
extern char *draft;
extern char *fileproc;
extern char *foldprot;
extern char *formatproc;
extern char *forwcomps;
extern char *inbox;
extern char *incproc;
extern char *lproc;
extern char *mailproc;
extern char *mh_defaults;
extern char *mh_profile;
extern char *mh_seq;
extern char *mhlformat;
extern char *mhlforward;
extern char *mhlproc;
extern char *mhlreply;
extern char *moreproc;
extern char *msgprot;
extern char *nmhaccessftp;
extern char *nmhaccessurl;
extern char *nmhstorage;
extern char *nmhcache;
extern char *nmhprivcache;
extern char *nsequence;
extern char *packproc;
extern char *postproc;
extern char *pfolder;
extern char *psequence;
extern char *rcvdistcomps;
extern char *rcvstoreproc;
extern char *replcomps;
extern char *replgroupcomps;
extern char *rmmproc;
extern char *sendproc;
extern char *showmimeproc;
extern char *showproc;
extern char *usequence;
extern char *version_num;
extern char *version_str;
extern char *whatnowproc;
extern char *whomproc;

extern void (*done) (int) NORETURN;

#include <h/prototypes.h>


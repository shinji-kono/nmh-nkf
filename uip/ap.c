
/*
 * ap.c -- parse addresses 822-style
 *
 * This code is Copyright (c) 2002, by the authors of nmh.  See the
 * COPYRIGHT file in the root directory of the nmh distribution for
 * complete copyright information.
 */

#include <h/mh.h>
#include <h/addrsbr.h>
#include <h/fmt_scan.h>
#include <h/mts.h>
#include <h/utils.h>

#define	NADDRS	100

#define	WIDTH	78

#define	FORMAT	"%<{error}%{error}: %{text}%|%(putstr(proper{text}))%>"

#define AP_SWITCHES \
    X("form formatfile", 0, FORMSW) \
    X("format string", 5, FMTSW) \
    X("width columns", 0, WIDTHSW) \
    X("version", 0, VERSIONSW) \
    X("help", 0, HELPSW) \

#define X(sw, minchars, id) id,
DEFINE_SWITCH_ENUM(AP);
#undef X

#define X(sw, minchars, id) { sw, minchars, id },
DEFINE_SWITCH_ARRAY(AP, switches);
#undef X

static struct format *fmt;

static int dat[5];

/*
 * static prototypes
 */
static int process (char *, int);


int
main (int argc, char **argv)
{
    int addrp = 0;
    int width = -1, status = 0;
    char *cp, *form = NULL, *format = NULL, *nfs;
    char buf[BUFSIZ], **argp;
    char **arguments, *addrs[NADDRS];

    if (nmh_init(argv[0], 1)) { return 1; }

    mts_init (invo_name);
    arguments = getarguments (invo_name, argc, argv, 1);
    argp = arguments;

    while ((cp = *argp++)) {
	if (*cp == '-') {
	    switch (smatch (++cp, switches)) {
		case AMBIGSW: 
		    ambigsw (cp, switches);
		    done (1);

		case UNKWNSW: 
		    adios (NULL, "-%s unknown", cp);

		case HELPSW: 
		    snprintf (buf, sizeof(buf), "%s [switches] addrs ...",
			invo_name);
		    print_help (buf, switches, 1);
		    done (0);
		case VERSIONSW:
		    print_version (invo_name);
		    done (0);

		case FORMSW: 
		    if (!(form = *argp++) || *form == '-')
			adios (NULL, "missing argument to %s", argp[-2]);
		    format = NULL;
		    continue;
		case FMTSW: 
		    if (!(format = *argp++) || *format == '-')
			adios (NULL, "missing argument to %s", argp[-2]);
		    form = NULL;
		    continue;

		case WIDTHSW: 
		    if (!(cp = *argp++) || *cp == '-')
			adios (NULL, "missing argument to %s", argp[-2]);
		    width = atoi (cp);
		    continue;
	    }
	}
	if (addrp > NADDRS)
	    adios (NULL, "more than %d addresses", NADDRS);
	else
	    addrs[addrp++] = cp;
    }
    addrs[addrp] = NULL;

    if (addrp == 0)
	adios (NULL, "usage: %s [switches] addrs ...", invo_name);

    /* get new format string */
    nfs = new_fs (form, format, FORMAT);

    if (width == -1) {
	if ((width = sc_width ()) < WIDTH / 2) {
	    /* Default:  width of the terminal, but at least WIDTH/2. */
	    width = WIDTH / 2;
	}
	width -= 2;
    } else if (width == 0) {
	/* Unlimited width.  */
	width = INT_MAX;
    }
    fmt_compile (nfs, &fmt, 1);

    dat[0] = 0;
    dat[1] = 0;
    dat[2] = 0;
    dat[3] = width;
    dat[4] = 0;

    for (addrp = 0; addrs[addrp]; addrp++)
	status += process (addrs[addrp], width);

    fmt_free (fmt, 1);
    done (status);
    return 1;
}

struct pqpair {
    char *pq_text;
    char *pq_error;
    struct pqpair *pq_next;
};


static int
process (char *arg, int length)
{
    int	status = 0;
    register char *cp;
    char error[BUFSIZ];
    register struct comp *cptr;
    register struct pqpair *p, *q;
    struct pqpair pq;
    register struct mailname *mp;

    (q = &pq)->pq_next = NULL;
    while ((cp = getname (arg))) {
	if ((p = (struct pqpair *) mh_xcalloc ((size_t) 1, sizeof(*p))) == NULL)
	    adios (NULL, "unable to allocate pqpair memory");
	if ((mp = getm (cp, NULL, 0, error, sizeof(error))) == NULL) {
	    p->pq_text = getcpy (cp);
	    p->pq_error = getcpy (error);
	    status++;
	}
	else {
	    p->pq_text = getcpy (mp->m_text);
	    mnfree (mp);
	}
	q = (q->pq_next = p);
    }

    for (p = pq.pq_next; p; p = q) {
	charstring_t scanl =
	    charstring_create (length < NMH_BUFSIZ ? length : NMH_BUFSIZ);

	cptr = fmt_findcomp ("text");
	if (cptr) {
	    if (cptr->c_text)
		free(cptr->c_text);
	    cptr->c_text = p->pq_text;
	    p->pq_text = NULL;
	}
	cptr = fmt_findcomp ("error");
	if (cptr) {
	    if (cptr->c_text)
		free(cptr->c_text);
	    cptr->c_text = p->pq_error;
	    p->pq_error = NULL;
	}

	fmt_scan (fmt, scanl, length, dat, NULL);
	fputs (charstring_buffer (scanl), stdout);
	charstring_free (scanl);

	if (p->pq_text)
	    free (p->pq_text);
	if (p->pq_error)
	    free (p->pq_error);
	q = p->pq_next;
	free ((char *) p);
    }

    return status;
}

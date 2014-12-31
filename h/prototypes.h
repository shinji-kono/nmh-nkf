
/*
 * prototypes.h -- various prototypes
 *
 * If you modify functions here, please document their current behavior
 * as much as practical.
 */

/*
 * prototype from config.h
 */
char *etcpath(char *);

/*
 * prototypes from the nmh subroutine library
 */

struct msgs_array;

void add_profile_entry (const char *, const char *);
void adios (char *, char *, ...) NORETURN;
void admonish (char *, char *, ...);
void advertise (char *, char *, char *, va_list);
void advise (char *, char *, ...);
char **argsplit (char *, char **, int *);
void argsplit_msgarg (struct msgs_array *, char *, char **);
void argsplit_insert (struct msgs_array *, char *, char **);
void arglist_free (char *, char **);
void ambigsw (char *, struct swit *);
int atooi(char *);
char **brkstring (char *, char *, char *);

/*
 * Check to see if we can display a given character set natively.
 * Arguments include:
 *
 * str	- Name of character set to check against
 * len	- Length of "str"
 *
 * Returns 1 if the specified character set can be displayed natively,
 * 0 otherwise.
 */

int check_charset (char *, int);
int client(char *, char *, char *, int, int);
void closefds(int);
char *concat (const char *, ...);
int context_del (char *);
char *context_find (const char *);
char *context_find_by_type (const char *, const char *, const char *);
int context_foil (char *);
void context_read (void);
void context_replace (char *, char *);
void context_save (void);
char *copy (const char *, char *);
char **copyip (char **, char **, int);
void cpydata (int, int, char *, char *);
void cpydgst (int, int, char *, char *);
char *cpytrim (const char *);
char *rtrim (char *);
int decode_rfc2047 (char *, char *, size_t);
void discard (FILE *);
char *upcase (const char *);

/*
 * Decode two characters into their quoted-printable representation.
 *
 * Arguments are:
 *
 * byte1	- First character of Q-P representation
 * byte2	- Second character of Q-P representation
 *
 * Returns the decoded value, -1 if the conversion failed.
 */
int decode_qp(unsigned char byte1, unsigned char byte2);

int default_done (int);

/*
 * Encode a message header using RFC 2047 encoding.  If the message contains
 * no non-ASCII characters, then leave the header as-is.
 *
 * Arguments include:
 *
 * name		- Message header name
 * value	- Message header content; must point to allocated memory
 *		  (may be changed if encoding is necessary)
 * encoding	- Encoding type.  May be one of CE_UNKNOWN (function chooses
 *		  the encoding), CE_BASE64 or CE_QUOTED
 * charset	- Charset used for encoding.  If NULL, obtain from system
 *		  locale.
 *
 * Returns 0 on success, any other value on failure.
 */

int encode_rfc2047(const char *name, char **value, int encoding,
		   const char *charset);

void escape_display_name (char *, size_t);
void escape_local_part (char *, size_t);
int ext_hook(char *, char *, char *);
int fdcompare (int, int);
int folder_addmsg (struct msgs **, char *, int, int, int, int, char *);
int folder_delmsgs (struct msgs *, int, int);
void folder_free (struct msgs *);
int folder_pack (struct msgs **, int);

/*
 * Read a MH folder structure and return an allocated "struct msgs"
 * corresponding to the contents of the folder.
 *
 * Arguments include:
 *
 * name		- Name of folder
 * lockflag	- If true, write-lock (and keep open) metadata files.
 *		  See comments for seq_read() for more information.
 */
struct msgs *folder_read (char *name, int lockflag);

struct msgs *folder_realloc (struct msgs *, int, int);
int gans (char *, struct swit *);
char **getans (char *, struct swit *);
#ifdef READLINE_SUPPORT
char **getans_via_readline (char *, struct swit *);
#endif /* READLINE_SUPPORT */
int getanswer (char *);
char **getarguments (char *, int, char **, int);

/*
 * Returns the MIME character set indicated by the current locale setting.
 * Should be used by routines that want to convert to/from the local
 * character set, or if you want to check to see if you can display content
 * in the local character set.
 */
char *get_charset(void);

char *getcpy (const char *);
char *get_default_editor(void);
char *getfolder(int);

/*
 * Get a string from the terminfo database for the current terminal.
 *
 * Retrieve the specified terminfo capability and return a string that
 * can be output to the terminal.  The string returned has already been
 * processed by tputs(), so it is safe to output directly.  The return
 * value of this function is valid until the next call.
 *
 * Arguments:
 *
 * capability	- The name of the terminfo capability (see terminfo(5)).
 *
 * Returns a tputs-processed string, or NULL if terminal initialization failed
 * or the capability wasn't found.
 */
char *get_term_stringcap(char *capability);

/*
 * Get a parameterized string from the terminfo database for the current
 * terminal.
 *
 * We don't yet have a standardized tparm() that will take a stdarg
 * argument.  Right now we don't want many parameters, so we only
 * take two.  Everything gets passed to tparm() as-is.  If we need
 * a capability with more arguments, we'll just add more later.
 *
 * Arguments:
 *
 * capability	- The name of the terminfo capability (see terminfo(5)).
 * arg1..argN	- Arguments 1-N.
 *
 * Returns a tparm and tputs-processed string, or NULL if there was a problem
 * initializating the terminal or retrieving the capability.
 */
char *get_term_stringparm(char *capability, long arg1, long arg2);

/*
 * Get a number from the terminfo database for the current terminal.
 *
 * Retrieve the specified terminfo capability and return the numeric
 * value of that capability from the terminfo database.
 *
 * Arguments:
 *
 * capability	- The name of the terminfo capability (see terminfo(5)).
 *
 * Returns the output of tigetnum() for that capability, or -1 if it was
 * unable to initialize the terminfo database.
 */
int get_term_numcap(char *capability);

/*
 * Lock open/close routines.
 *
 * The lk[f]opendata() functions are designed to open "data" files (anything
 * not a mail spool file) using the locking mechanism configured for data
 * files.  The lk[f]openspool() functions are for opening the mail spool
 * file, which will use the locking algorithm configured for the mail
 * spool.
 *
 * Files opened for reading are locked with a read lock (if possible by
 * the underlying lock mechanism), files opened for writing are locked
 * using an exclusive lock.  The int * argument is used to indicate failure
 * to acquire a lock.
 */
int lkclosedata(int, const char *);
int lkclosespool(int, const char *);
int lkfclosedata(FILE *, const char *);
int lkfclosespool(FILE *, const char *);
FILE *lkfopendata(const char *, const char *, int *);
int lkopendata(const char *, int, mode_t, int *);
FILE *lkfopenspool(const char *, const char *);
int lkopenspool(const char *, int, mode_t, int *);
int m_atoi (char *);
char *m_backup (char *);
int m_convert (struct msgs *, char *);
char *m_draft (char *, char *, int, int *);
void m_getfld_state_reset (m_getfld_state_t *);
void m_getfld_state_destroy (m_getfld_state_t *);
void m_getfld_track_filepos (m_getfld_state_t *, FILE *);
int m_getfld (m_getfld_state_t *, char[NAMESZ], char *, int *, FILE *);
int m_gmprot (void);
char *m_maildir (char *);
char *m_mailpath (char *);
char *m_name (int);
int m_putenv (char *, char *);
int m_rand (unsigned char *, size_t);
char *m_mktemp(const char *, int *, FILE **);
char *m_mktemp2(const char *, const char *, int *, FILE **);
char *m_mktemps(const char *pfx, const char *suffix, int *, FILE **);
char *get_temp_dir();

/*
 * Create a subprocess and redirect our standard output to it.
 *
 * Arguments are:
 *
 * name		- Name of process to create
 * savestdout	- If true, will save the current stdout file descriptor and
 *		  m_pclose() will close it at the appropriate time.
 */
void m_popen(char *name, int savestdout);

/*
 * Wait for the last process opened by m_popen().
 */
void m_pclose(void);

void m_unknown(m_getfld_state_t *, FILE *);
int makedir (char *);
char *message_id (time_t, int);

/*
 * Return a MIME content-type string for the specified file.
 *
 * If the system supports it, will use the "file" command to determine
 * the appropriate content-type.  Otherwise it will try to determine the
 * content-type from the suffix.  If that fails, the file will be scanned
 * and either assigned a MIME type of text/plain or application/octet-stream
 * depending if binary content is present.
 *
 * Arguments:
 *
 * filename	- The name of the file to determine the MIME type of.
 *
 * Returns a pointer to a content-type string (which may include MIME
 * parameters, such as charset).  Returns a NULL if it cannot determine
 * the MIME type of the file.  Returns allocated storage that must be
 * free'd.
 */
char *mime_type(const char *filename);

/*
 * Clear the screen, using the appropriate entry from the terminfo database
 */
void nmh_clear_screen(void);
char *nmh_getpass(const char *);
char *new_fs (char *, char *, char *);
char *path(char *, int);
int peekc(FILE *ib);
int pidwait (pid_t, int);
int pidstatus (int, FILE *, char *);
char *pluspath(char *);
void print_help (char *, struct swit *, int);
void print_sw (char *, struct swit *, char *, FILE *);
void print_version (char *);
void push (void);
char *pwd (void);
char *r1bindex(char *, int);
void readconfig (struct node **, FILE *, char *, int);
int refile (char **, char *);
void ruserpass (char *, char **, char **);
int remdir (char *);
void scan_detect_mbox_style (FILE *);
void scan_finished ();
void scan_reset_m_getfld_state ();
int seq_addmsg (struct msgs *, char *, int, int, int);
int seq_addsel (struct msgs *, char *, int, int);
char *seq_bits (struct msgs *);
int seq_delmsg (struct msgs *, char *, int);
int seq_delsel (struct msgs *, char *, int, int);
int seq_getnum (struct msgs *, char *);
char *seq_list (struct msgs *, char *);
int seq_nameok (char *);
void seq_print (struct msgs *, char *);
void seq_printall (struct msgs *);

/*
 * Read the sequence files for the folder referenced in the given
 * struct msgs and populate the sequence entries in the struct msgs.
 *
 * Arguments:
 *
 * mp		- Folder structure to add sequence entries to
 * lockflag	- If true, obtain a write lock on the sequence file.
 *		  Additionally, the sequence file will remain open
 *		  and a pointer to the filehandle will be stored in
 *		  folder structure, where it will later be used by
 *		  seq_save().
 *
 * Return values:
 *     OK       - successfully read the sequence files, or they don't exist
 *     NOTOK    - failed to lock sequence file
 */
int seq_read (struct msgs * mp, int lockflag);
void seq_save (struct msgs *);
void seq_setcur (struct msgs *, int);
void seq_setprev (struct msgs *);
void seq_setunseen (struct msgs *, int);
int showfile (char **, char *);
int smatch(char *, struct swit *);

/*
 * Convert a set of bit flags to printable format.
 *
 * Arguments:
 *
 * buffer	- Buffer to output string to.
 * size		- Size of buffer in bytes.  Buffer is always NUL terminated.
 * flags	- Binary flags to output
 * bitfield	- Textual representation of bits to output.  This string
 *		  is in the following format:
 *
 *	Option byte 0x01 STRING1 0x02 STRING2 ....
 *
 * The first byte is an option byte to snprintb().  Currently the only option
 * supported is 0x08, which indicates that the flags should be output in
 * octal format; if the option byte is any other value, the flags will be
 * output in hexadecimal.
 *
 * After the option bytes are series of text strings, prefixed by the number
 * of the bit they correspond to.  For example, the bitfield string:
 *
 *	"\020\01FLAG1\02FLAG2\03FLAG3\04FLAG4"
 *
 * will output the following string if "flags" is set to 0x09:
 *
 *	0x2<FLAG1,FLAG4>
 *
 * You don't have to use octal in the bitfield string, that's just the
 * convention currently used by the nmh code.  The order of flags in the
 * bitfield string is not significant, but again, general convention is
 * from least significant bit to most significant.
 */
char *snprintb (char *buffer, size_t size, unsigned flags, char *bitfield);
int ssequal (char *, char *);
int stringdex (char *, char *);
char *trimcpy (char *);
int unputenv (char *);

/*
 * Remove quotes and quoted-pair sequences from RFC-5322 atoms.
 *
 * Currently the actual algorithm is simpler than it technically should
 * be: any quotes are simply eaten, unless they're preceded by the escape
 * character (\).  This seems to be sufficient for our needs for now.
 *
 * Arguments:
 *
 * input	- The input string
 * output	- The output string; is assumed to have at least as much
 *		  room as the input string.  At worst the output string will
 *		  be the same size as the input string; it might be smaller.
 *
 */
void unquote_string(const char *input, char *output);
int uprf (const char *, const char *);
int vfgets (FILE *, char **);

/*
 * Output the local character set name, but make sure it is suitable for
 * 8-bit characters.
 */
char *write_charset_8bit (void);


/*
 * some prototypes for address parsing system
 * (others are in addrsbr.h)
 */
char *LocalName(int);
char *SystemName(void);

/*
 * prototypes for some routines in uip
 */
int annotate (char *, char *, char *, int, int, int, int);
void annolist(char *, char *, char *, int);
void annopreserve(int);
void m_pclose(void);
int make_intermediates(char *);
int mhl(int, char **);
int mhlsbr(int, char **, FILE *(*)(char *));
int distout (char *, char *, char *);
void replout (FILE *, char *, char *, struct msgs *, int,
	int, char *, char *, char *, int);
int sc_length(void);
int sc_width(void);
int build_form (char *, char *, int *, char *, char *, char *, char *,
		char *, char *);
int sendsbr (char **, int, char *, char *, struct stat *, int);
int SOprintf (char *, ...);
int what_now (char *, int, int, char *, char *,
	int, struct msgs *, char *, int, char *, int);
int WhatNow(int, char **);

/*
 * Copy data from one file to another, converting to base64-encoding.
 *
 * Arguments include:
 *
 * in		- Input filehandle (unencoded data)
 * out		- Output filename (base64-encoded data)
 * crlf		- If set, output encoded CRLF for every LF on input.
 *
 * Returns OK on success, NOTOK otherwise.
 */
int writeBase64aux(FILE *in, FILE *out, int crlf);

int writeBase64 (unsigned char *, size_t, unsigned char *);
int writeBase64raw (unsigned char *, size_t, unsigned char *);

/*
 * credentials management
 */
void init_credentials_file ();
int nmh_get_credentials (char *, char *, int, nmh_creds_t);

/*
 * temporary file management
 */
int nmh_init(const char *argv0, int read_context);
int m_unlink(const char *);
void unregister_for_removal(int remove_files);

/*
 * General decode routine using nkf
 *
 * Arguments are:
 *
 * s		- input string (will be overriden)
 * encode        - Content-Transfer-Encoding in mhparse.h
 * charset       - coding system  in mhparse.h 
 *
 * Returns modified string actualy s itself
 */
char * ml_conv_decode(char *s,int encode,int charset);


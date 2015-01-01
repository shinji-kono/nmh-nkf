=encoding euc-jp

=head1 NAME

nkf - �ͥåȥ���Ѵ����������Ѵ��ե��륿

=head1 SYNOPSIS

nkf B<[-butjnesliohrTVvwWJESZxXFfmMBOcdILg]> B<[>I<file ...>B<]>

=head1 DESCRIPTION

B<nkf> �ϥͥåȥ���ǥ᡼���˥塼�����ɤ߽񤭤򤹤뤿��˺��줿�����������ɤ��Ѵ��ե��륿�Ǥ��롣

����B<nkf>����ħ�Ȥ��Ƥϡ����ϴ��������ɷϤ�����Ū�ʼ�ưǧ����ǽ�����롣
���Τ��ᡢ���ѼԤϡ����ϴ��������ɷϤ����Ǥ��뤫���Τ�ʤ��Ƥ⡢���ϴ��������ɷϤΤ߻��ꤹ����ɤ����Ȥˤʤ롣
����������Ƚ�굡���ϡ�����Ū�ˤϴ����ǤϤʤ������̾�Υ˥塼����᡼��Υ�å������ˤĤ��Ƥϳμ¤�ư�������ʤ�ΤˤϤʤäƤ��롣

���ߡ�B<nkf>��ǧ���Ǥ������Ϥδ��������ɷϤϡ������� JIS ������ (ISO-2022-JP �˴�Ť����)��Shift_JIS (MS ����������)��
���ܸ� EUC (AT&T ������)��UTF-8��UTF-16 �Τ����줫�Ǥ��롣
���Ϥ�����������ɷϤ⡢�����Ǥ��롣
���Ϥϡ��ե��������ꤷ�ʤ���С�ɸ�����ϤȤʤ롣
���Ϥ�ɸ����ϤǤ��롣


=head1 OPTIONS

����Ǥ��륪�ץ����ϡ��ʲ����̤ꡣ
B<-mu> �Τ褦��³���뤳�Ȥ��Ǥ��롣

=over

=item B<-j>

JIS �����ɤ���Ϥ��롣

=item B<-e>

EUC �����ɤ���Ϥ��롣

=item B<-s>

Shift_JIS �����ɤ���Ϥ��롣

=item B<-w -w8[0] -w16[BL][0]>

Unicode ����Ϥ��롣

=over

=item B<-w -w80>

UTF8 �����ɤ���Ϥ��롣 (BOM ̵��)

=item B<-w8>

UTF8 �����ɤ���Ϥ��롣

=item B<-w16 -w16B0>

UTF16 �����ɤ���Ϥ��롣 (Big Endian / BOM ̵��)

=item B<-w16B>

UTF16 �����ɤ���Ϥ��롣 (Big Endian / BOM ͭ��)

=item B<-w16L>

UTF16 �����ɤ���Ϥ��롣 (Little Endian / BOM ͭ��)

=item B<-w16L0>

UTF16 �����ɤ���Ϥ��롣 (Little Endian / BOM ̵��)

=back

=item B<-m[BQSN0]>

MIME ����ɤ��롣(�ǥե����)
ISO-2022-JP (B encode) �� ISO-8859-1 (Q encode) �Τߤ���ɤ��롣
ISO-8859-1 (Latin-1) ����ɤ�����ϡ�B<-l> �ե饰��ɬ�פǤ��롣
B<-m0> �Ǥ� MIME ����ɤ��ʤ���
B<-mB>, B<-mQ> �Ǥϡ�BASE64, Q encode ����Ƥ����ΤȤ��ƽ������롣

=over

=item B<-mB>

MIME base64 stream ����ɤ��롣
�إå��ʤɤϼ��������ȡ�

=item B<-mQ>

MIME quoted stream ����ɤ��롣

=item B<-mS>

MIME �Υ����å��򸷤������� (�ǥե����)

=item B<-mN>

MIME �Υ����å���ˤ�����

=item B<-m0>

MIME ����ɤ��ʤ���

=back

B<-mS> �ϡ���������Ƥȡ����θ��³�� encoded-text ��������������å����롣
B<-mN> �ϡ����Ԥ��ڤ�줿 MIME �ʤɤ���ɤ��롣���ɤ��ߤޤ�ʤ����Ȥ⤢�롣

=item B<-M[BQ]>

MIME ���Ѵ����롣

=over

=item B<-M>

�إå��������Ѵ�����

=item B<-MB>

base64 stream ���Ѵ�����

=item B<-MQ>

Quoted stream ���Ѵ�����

=back

=item B<-J -E -S -W>

���Ԥ�������ϥ����ɤ���������ꤹ�롣

=over

=item B<-J>

ISO-2022-JP ���ꤹ�롣

=item B<-E>

���ܸ� EUC (AT&T) ���ꤹ�롣

=item B<-S>

Shift_JIS ���ꤹ�롣
������Ⱦ�ѥ��� (JIS X 0201 �Ҳ�̾) ���������롣

=item B<-W>

UTF-8 ���ꤹ�롣

=item B<-W8>

UTF-8 ���ꤹ�롣

=item B<-W16>

UTF-16 (Little Endian)���ꤹ�롣

=item B<-W16B>

UTF-16 (Big Endian)���ꤹ�롣

=item B<-W16L>

UTF-16 (Little Endian)���ꤹ�롣

=back

=item B<-x>

�̾浪���ʤ��롢������Ⱦ�ѥ��� (JIS X 0201 �Ҳ�̾)
���餤�������ѥ��� (JIS X 0208 �Ҳ�̾) �ؤ��Ѵ���Ԥ鷺��Ⱦ�ѥ��ʤ���¸���롣
���Ϥϡ�Shift_JIS �� 1byte ���ʡ�SO/SI��ESC-(-I, SSO ������դ��롣
���Ϥϡ����ܸ� EUC ��Ǥ� SSO��JIS ��������Ǥ� ESC-(-I ��ǥե���Ȥ��Ѥ��롣

=item B<-X>

������Ⱦ�ѥ��� (JIS X 0201 �Ҳ�̾) �� ���������ѥ��� (JIS X 0208 �Ҳ�̾) �ؤ��Ѵ����롣

=item B<-B>

���줿 (Broken) JIS �����ɡ�
ESC ���ʤ��ʤä��Ȳ��ꤹ�롣

=over

=item B<-B1>

B<ESC-(>, B<ESC-$> �Τ��ȤΥ����ɤ����ʤ�

=item B<-B2>

���ԤΤ��Ȥ˶���Ū�� ASCII ���᤹

=back

=item B<-f>[I<m>[-I<n>]]

��� I<m> ʸ���ˤʤ�褦�ˡ��ޡ������ I<n> �Ȥ��ƴ�ñ�������򤪤��ʤ���
�ǥե���Ȥ�ʸ������ 60���ޡ������ 10 �Ǥ��롣

=item B<-Z[0-3]>

JIS X 0208 �ѿ����ȼ㴳�ε���� ASCII ���Ѵ����롣
�Ĥޤꡢ���Ѥ�Ⱦ�Ѥ��Ѵ����롣

=over

=item B<-Z -Z0>

Convert X0208 alphabet to ASCII.

=item B<-Z1>

JIS X 0208 �»��ֳ֤� ASCII space ��Ĥ��Ѵ����롣

=item B<-Z2>

JIS X 0208 �»��ֳ֤� ASCII space ��Ĥ��Ѵ����롣

=item B<-Z3>

�䡢�㡢�ɡ������� &gt;��&lt;��&quot;��&amp; ���Ѵ����롣

=back

=item B<-b>

�Хåե���󥰽��Ϥ�Ԥ���(�ǥե����)

=item B<-u>

���ϻ��ˡ��Хåե���󥰤��ʤ���
ssh localhost | nkf -u �Ȥ����褦�˻Ȥ���

=item B<-t>

���⤷�ʤ���

=item B<-I>

ISO-2022-JP �ʳ��δ��������ɤ򢮤��Ѵ���

=item B<-i[@B]>

JIS ������ؼ����륷�����󥹤���ꤹ�롣

=over

=item B<-i@>

JIS X 0208-1978 ���Ѥ��롣

=item B<-iB>

JIS X 0208-1983/1990 ���Ѥ��롣

=back

=item B<-o[BJH]>

1 �Х��ȱѿ�ʸ�����åȤ�ؼ����륷�����󥹤���ꤹ�롣

=over

=item B<-oB>

1 �Х��ȱѿ�ʸ�����åȤȤ��� US-ASCII ���Ѥ��롣

=item B<-oJ>

1 �Х��ȱѿ�ʸ�����åȤȤ��� JIS X 0201 Roman ���Ѥ��롣

=item B<-oH>

ESC ( H �Ͻ���� JUNET �����ɤǤΤ��Ѥ���줿��Τǡ����ߤϻȤäƤϤʤ�ʤ���

=back

=item B<-r>

ROT13/47 ���Ѵ��򤹤롣

=item B<-g>

��ưȽ�̤η�̤���Ϥ��ޤ���

=item B<-T>

�ƥ����ȥ⡼�ɤǽ��Ϥ��롣(MS-DOS ��ǤΤ߸��Ϥ����)

=item B<-l>

0x80-0xfe �Υ����ɤ� ISO-8859-1 (Latin-1) �Ȥ��ư�����
JIS �����ɥ����ȥץåȤȤ��ȹ礻�ߤΤ�ͭ����
B<-s, -e, -x> �Ȥ�ξΩ���ʤ���

=item B<-O>

�ե�����˽��Ϥ��롣
UNIX �Ǥ����פʵ�ǽ���� Windows �� MSDOS �Ǥ�ɬ�פ餷����
ľ��ΰ������Ǥʤ����Ǹ�Υե�����̾�����ϥե�����̾�Ȥʤ��񤭤���Ƥ��ޤ��Τ���ա�
�ե�����̾���ʤ����� nkf.out��

=item B<-L[uwm] -d -c>

���ԥ����ɤ��Ѵ����롣

=over

=item B<-Lu -d>

unix (LF)

=item B<-Lw -c>

windows (CRLF)

=item B<-Lm>

mac (CR)

=back

�ǥե���ȤǤ��Ѵ����ʤ���

=item B<--ic=<input_codeset> --oc=<output_codeset>>

���ϡ����Ϥδ��������ɷϤ���ꤷ�ޤ���

=over

=item B<ISO-2022-JP>

������ JIS �����ɡ�B<-j, -J> ��Ʊ����

=item B<ISO-2022-JP-1>

RFC 2237 ������줿������ JIS X 0212 ��ޤࡣ

=item B<ISO-2022-JP-3>

RFC 2237 ������줿������ JIS X 0213 ��ޤࡣ

=item B<EUC-JP>

EUC �����ɡ�B<-e, -E> ��Ʊ����

=item B<EUC-JISX0213>

ʸ������� JIS X 0213:2000 ���Ѥ��� EUC-JP��

=item B<EUC-JIS-2004>

ʸ������� JIS X 0213:2004 ���Ѥ��� EUC-JP��

=item B<eucJP-ascii>

�����ץ󥰥롼�����ܥ٥�����Ĳ�������� eucJP-ascii��
B<-x> �����ۤΤ����˻��ꤵ��롣

=item B<eucJP-ms>

�����ץ󥰥롼�����ܥ٥�����Ĳ�������� euc-JPms��
B<-x> �����ۤΤ����˻��ꤵ��롣

=item B<CP51932>

Micorosft Code Page 51932��
B<-x> �����ۤΤ����˻��ꤵ��롣

=item B<Shift_JIS>

Shift_JIS��
B<-s, -S> ��Ʊ����

=item B<Shift_JISX0213>

ʸ������� JIS X 0213:2000 ���Ѥ��� Shift_JIS��

=item B<Shift_JIS-2004>

ʸ������� JIS X 0213:2004 ���Ѥ��� Shift_JIS��

=item B<CP932>

Micorosft Code Page 932��
B<-x> �����ۤΤ����˻��ꤵ��롣

=item B<UTF-8 UTF-8N>

BOM ̵���� UTF-8��
B<-w, -W> ��Ʊ����

=item B<UTF-8-BOM>

BOM �դ��� UTF-8��B<-w8> �ޤ��� B<-W> ��Ʊ����

=item B<UTF8-MAC>

UTF8-MAC���ߴ�ʬ�򤵤줿�Ҥ餬�ʡ��������������礷�ޤ���
���ϤΤߤ��б��Ǥ���

=item B<UTF-16 UTF-16BE-BOM>

BOM ͭ��� Big Endian �� UTF-16��
B<-w16B, -W16B> ��Ʊ����

=item B<UTF-16BE>

BOM ̵���� Big Endian �� UTF-16��
B<-w16B0. -W16B> ��Ʊ����

=item B<UTF-16LE-BOM>

BOM ͭ��� Little Endian �� UTF-16��
B<-w16L, -W16L> ��Ʊ����

=item B<UTF-16LE>

BOM ̵���� Little Endian �� UTF-16��
B<-w16L0, -W16L> ��Ʊ����

=back

=item B<--fj --unix --mac --msdos  --windows>

�����Υ����ƥ��Ŭ�����Ѵ��򤷤ޤ���


=item B<--jis --euc --sjis --mime --base64>

�б������Ѵ��򤷤ޤ���

=item B<--hiragana --katakana>

ʿ��̾���Ҳ�̾�Ѵ�

=item B<--fb-{skip, html, xml, perl, java, subchar}>

Unicode ���� Shift_JIS, EUC-JP, ISO-2022-JP ���Ѵ�����ݤˡ��Ѵ��Ǥ��ʤ��ä�ʸ����ɤ������������Ǥ��ޤ���

=item B<--prefix=I<escape character>I<target character>..>

EUC-JP ���� Shift_JIS �ؤ��Ѵ��κݡ�2 �Х�����
�˸��줿ʸ�������˥���������ʸ����Ĥ��뤳�Ȥ��Ǥ��ޤ���
������ 1 ʸ���ܤ�����������ʸ����2 ʸ���ܰʹߤ˥��������פ����٤�ʸ������ꤷ�ޤ���

�㤨�С�

--prefix=\$@ �Ȥ���ȡ�Shift_JIS �� 2 ʸ���ܤ� $ �� @ ���褿�顢�������� \ ����������ޤ�
--prefix=@@ �Ȥ���ȡ�Shift_JIS �� 2 ʸ���ܤ� @ ���褿�顢�������� @ ����������ޤ�

=item B<--no-cp932ext>

CP932 �ˤ����Ƴ�ĥ���줿��NEC �ü�ʸ����NEC ���� IBM ��ĥʸ�� (89-92 ��)��IBM ��ĥʸ�����Ѵ����ޤ���

=item B<--no-best-fit-chars>

Unicode ������Ѵ��κݤˡ����������������ݤ���ʤ�ʸ�����Ѵ���Ԥ��ޤ���
Unicode ���� Unicode ���Ѵ��κݤ� -x �ȶ��˻��ꤹ��ȡ�nkf �� UTF �������Ѵ����Ѥ��뤳�Ȥ��Ǥ��ޤ���
(�դ˸����С��������ꤷ�ʤ��Ȱ�����ʸ������¸����ޤ���)

�ѥ��˴ؤ��ʸ������Ѵ�����ݤˤϡ����Υ��ץ�������ꤹ�뤳�Ȥ򶯤��侩���ޤ���

=item B<--cap-input, --url-input>

���줾�� :��% ��³�� 16 �ʿ���ʸ�����Ѵ�����

=item B<--numchar-input>

&#....; �Τ褦�� Unicode ʸ�����Ȥ��Ѵ�����

=item B<--in-place[=I<SUFFIX>]  --overwrite[=I<SUFFIX>]>

���Υե�������Ѵ���̤��֤������롣
ʣ���Υե������񤭴����뤳�Ȥ��ǽ��
���Υե�����Υ����ॹ����פȥѡ��ߥå�����ݻ�����롣
���ߡ����������� inode ���ѹ�����뤬������ˤ錄�äƤ��μ����ΤޤޤǤ����ݾڤ�̵����

=item B<--guess>

��ưȽ�̤η�̤���Ϥ���

=item B<--help>

���ޥ�ɤδ�ñ��������ɽ�����롣

=item B<-V>

nkf �������ɽ�����롣

=item B<-v> B<--version>

nkf �ΥС�������ɽ�����롣

=item B<-->

����ʹߤΥ��ץ�����̵�뤹��

=item B<--exec-in>

nkf [options] --exec-in cmd args... �Ȥ��ȡ�cmd �ν��Ϥ� nkf �����ϤȤ���
(config.h �� EXEC_IO �� define ���ƥ���ѥ��뤷�����Τ�ͭ��)

=item B<--exec-out>

nkf [options] --exec-out cmd args... �Ȥ��ȡ�nkf �ν��Ϥ� cmd �����ϤȤ���
(config.h �� EXEC_IO �� define ���ƥ���ѥ��뤷�����Τ�ͭ��)

=back

=head1 BUGS

�¤ϡ����ϤΥ����ɷϤ�Ƚ��ϡ�Shift_JIS �� EUC �Ȥμ�ưȽ��Ǥ��ꡢ�ǽ������Ǥ���ʸ�����褿�����ǳ��ꤷ�Ƥ��ޤ���
�����ơ�������ǽ�δ֤���α�Хåե��ˤ���Ƥ����졢�����˽�������롣
���Τ��ᡢ7 �ӥå� JIS �Ͼ��ǧ������롣
Shift_JIS��EUC �����ۤȤ�ɤξ������꤬�ʤ���
��������Shift_JIS �Τ�����Ⱦ�ѥ��� (JIS X 0201 �Ҳ�̾) �� EUC ���������̤Ǥ��ʤ���
�������äơ��ǥե���ȤǤ� Shift_JIS �Τ�����Ⱦ�ѥ��ʤϤʤ��Ȳ��ꤷ�Ƥ��롣
(�ĤޤꡢShift_JIS �� EUC ���¤ä����� EUC �Ȥߤʤ�)

Unicode �����ܸ�ʳ�����ʬ���Ѵ��ˤ��б����Ƥ��ʤ�����B<--no-best-fit-chars> ����ꤹ��С�UTF-8 �� UTF-16 ������Ѵ��򤹤뤳�Ȥϲ�ǽ�Ǥ��롣

=head1 ACKNOWLEDGE

�ʲ��Τ����������ɤ��⤢�꤬�Ȥ��������ޤ�����

=head2 nkf 1.4

morb@fujitsu, kiss@ayumi.stars.flab.fujitsu, cen122@flab.fujitsu,
yuki@flab.fujitsu ¾��fujitsu & flab.fujitsu �γ�����ζ��Ϥ˴��ա�
shinoda@cs.titech, kato@cs.titech, uematsu@cs.titech  TNX
kono@ie.u-ryukyu.ac.jp
void@merope.pleiades.or.jp (Kusakabe Youichi)
NIDE Naoyuki <nide@ics.nara-wu.ac.jp>
ohta@src.ricoh.co.jp (Junn Ohta)
inouet@strl.nhk.or.jp (Tomoyuki Inoue)
kiri@pulser.win.or.jp (Tetsuaki Kiriyama)
Kimihiko Sato <sato@sail.t.u-tokyo.ac.jp>
a_kuroe@kuroe.aoba.yokohama.jp (Akihiko Kuroe)
kono@ie.u-ryukyu.ac.jp (Shinji Kono)
GHG00637@nifty-serve.or.jp (COW)

=head2 nkf 1.9-

=over

=item �����

=item Akio Furukawa

=item Andy Taki

=item From: OHARA Shigeki

=item Fumitaka Kitagawa

=item Hiroaki Sengoku

=item Ikuhiro MORITA (���� �鹨)

=item Yoshiharu ITO

=item Junn Ohta

=item KAWAMURA Masao

=item Kazuhiko Mori

=item Keitaro Isokawa

=item Ken-ichi Hirose

=item Ki-ichiro SATO

=item Kiwamu Aoyama

=item Koichi Hirayama

=item Mitsuru Hase (Ĺë����)

=item OHARA Shigeki (�縶 �ż�)

=item Rei FURUKAWA

=item Satoru Takabayashi

=item Shigeyuki Takagi

=item Shin MICHIMUKO

=item Tadamasa Teranishi

=item TOYODA Jiro

=item TSUCHIYA Masatoshi

=item Tsutomu Sakai

=item YAMASHITA Junji (���� ���)

=item Yasuyuki Sato

=item Yoshiaki Yanagihara

=item hat@so-net

=item �ģãõ���������

=item ���Ȥ� / ��ƣ ����

=item ����dais

=item �Ҥ� �ޤ�����

=item ����ȥ�ͥåȥ����ƥ�(��)����

=item ����ʸ��

=item ���� ��ɧ(SHIOZAKI Takehiko)

=item ��¼���� (Media Lab.)

=item ���� ����

=item ��������ǭ�ɹ��������

=item ��� ��ɧ

=item ���� ʹ�� (���Ĥ�� �ޤ���)

=item �ⶶ����

=item ���

=item ������ɧ

=item ��������

=item ���� ��

=item ���� ˧��

=item ����͵�� (��ޤΤ椦��)

=item ��¼ˡ��

=item �������

=item ���ġ���

=item ���� ���� (Koji Arai)

=item �����鳨��

=item ������ɧ

=item ���� ��ʸ

=item �����½�

=item �罡���������긦

=item ��ë �Ѱ�Ϻ == Eiichiro Itani

=item ƣ��������

=item Ȭ�� ���� (Masayuki Hatta)

=item ��������

=item ˾�� ����

=item ��¼ (��������ؿ��ظ����)

=item ��¼�Ӿ�

=item ͭ�����ߥΥ륿

=item ͭ�� ����

=item �����

=item ��  μ

=item Ԣ�� ��

=item �ڲ� ͺ��

=item ����δ͵

=item ��ëľ��

=item ���Ŀ���

=item �錄�ʤ٤Ҥ�դ�

=item MoonWolf

=item sava

=back

=head1 AUTHOR

=over

=item ����  ��        ichikawa@flab.fujitsu.co.jp (was ichikawa@fujitsu.JUNET)

=item ����  ����      kono@ie.u-ryukyu.acjp

=item Rei FURUKAWA    furukawa@tcp-ip.or.jp

=item ����

=item mastodon

=back

http://sourceforge.jp/projects/nkf/

Copyright (C) 1987, FUJITSU LTD. (I.Ichikawa).

Copyright (C) 1996-2013, The nkf Project.

=cut

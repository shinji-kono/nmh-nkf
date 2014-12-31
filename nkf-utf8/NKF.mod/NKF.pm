## Copyright (C) 1996,1998
## Copyright (C) 2002
## Ϣ���衧 ΰ����ؾ��󹩳ز� ���� ����  mime/X0208 support
## ��E-Mail Address: kono@ie.u-ryukyu.ac.jp��
## Ϣ���衧 COW for DOS & Win16 & Win32 & OS/2
## ��E-Mail Address: GHG00637@niftyserve.or.p��
##    
##    ���Υ������Τ����ʤ�ʣ�̡����ѡ�������������ޤ�����������
##    ���κݤˤϡ�ï���׸������򼨤�������ʬ��Ĥ����ȡ�
##    �����ۤ仨�����Ͽ�ʤɤ��䤤��碌��ɬ�פ���ޤ���
##    �������Ѥ�嵭��ȿ���ʤ��ϰϤǵ��Ĥ��ޤ���
##    �Х��ʥ�����ۤκݤˤ�version message����¸���뤳�Ȥ���Ȥ��ޤ���
##    ���Υץ����ˤĤ��Ƥ��ä˲����ݾڤ⤷�ʤ����������餺��
##    
##    Everyone is permitted to do anything on this program
##    including copying, modifying, improving, 
##    as long as you don't try to pretend that you wrote it.
##    i.e., the above copyright notice has to appear in all copies.  
##    Binar y distribution requires original version messages.
##    You don't have to ask before copying, redistribution or publishing.
##    THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE.


package NKF;

use strict;
use vars qw($VERSION @ISA @EXPORT @EXPORT_OK);

require Exporter;
require DynaLoader;

@ISA = qw(Exporter DynaLoader);
# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.
@EXPORT = qw(
	nkf	nkf_continue	inputcode
);
$VERSION = '2.05';

bootstrap NKF $VERSION;

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is the stub of documentation for your module. You better edit it!

=head1 NAME

NKF - Perl extension for Network Kanji Filter 

=head1 SYNOPSIS

  use NKF;
  $output = nkf("-s",$input);

=head1 DESCRIPTION

This is a Perl Extension version of nkf (Netowrk Kanji Filter ) 1.7.
It converts the last argument and return converted result. Conversion
details are specified by flags before the last argument.

Flags:

C<b,u      Output is bufferred (DEFAULT),Output is unbufferred>

C<j,s,e    Outout code is JIS 7 bit (DEFAULT), Shift JIS, AT&T JIS (EUC)>

C<J,S,E    Input assumption is JIS 7 bit , Shift JIS, AT&T JIS (EUC)>

C<t        no conversion>

C<i_       Output sequence to designate JIS-kanji (DEFAULT B)>

C<o_       Output sequence to designate ASCII (DEFAULT B)>

C<r        {de/en}crypt ROT13/47>

C<m[BQ]    MIME decode [B:base64 stream,Q:quoted stream]>

C<l        ISO8859-1 (Latin-1) support>

C<f        Folding: C<-f60> or C<-f>>

C<Z[0-2]   Convert X0208 alphabet to ASCII  1: Kankaku to space,2: 2 spaces>

C<X,x      Assume X0201 kana in MS-Kanji, C<-x> preserves X0201>

C<B[0-2]   Broken input  0: missing ESC,1: any X on ESC-[($]-X,2: ASCII on NL>

C<d,c      Delete \r in line feed, Add \r in line feed>


C<m0 No MIME decode.>

C<M MIME encode. Header style. All ASCII code and control characters are intact.>

C<MB MIME encode.  Base64 stream. Kanji conversion is performed before encoding, so this cannot be used as a picture encoder.>

C<l Input and output code is ISO8859-1 (Latin-1) and ISO-2022-JP.>

C<L[wmu] new line mode>

C<    -Lu   unix (LF) >

C<    -Lw   windows (CRLF) >

C<    -Lm   mac (CR) >

C< --fj,--unix,--mac,--msdos, --windows convert for these system>

C< --jis,--euc,--sjis,--mime,--base64  convert for named code>

C< --jis-input,--euc-input,--sjis-input,--mime-input,--base64-input assume input system>

C< -- ignore rest of -option>

C< --help>

C< --version>

=head1 AUTHOR

Network Kanji Filter Version 1.9 (2/0002/Shinji Kono) 
Copyright (C) 1987, FUJITSU LTD. (I.Ichikawa),1998 S. Kono, COW

=head1 SEE ALSO

perl(1).   nkf(1)

=cut

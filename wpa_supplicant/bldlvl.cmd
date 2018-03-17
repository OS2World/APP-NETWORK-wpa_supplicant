/*  REXX script to generate a buildlevel string. If file 'outfile' (see below)
    is found it will be updated with new values defined below. Otherwise it
    will be created. Uses enviroment variable %hostname% as build machine entry
    and current build date/time. Version is taken from ..\src\common\version.h.

    ---------------------------------------------------------------------------
    Arguments:
      ARG(1) when set 1 or 2 outputs additional messages usefull for debuging
      this script
    ---------------------------------------------------------------------------
    This file is part of WPA supplicant package for OS/2, ArcaOS, eComStation
    Copyright (c) 2014-2018, Andreas Buchinger
    ---------------------------------------------------------------------------
    History:
    20140831 AB   initial
    20180310 AB   update ArcaOS, OS/2
*/

VendorName = 'Andreas Buchinger'  /* no more than 31 chars */
BuildMachine = value('hostname',,'OS2ENVIRONMENT')
ASD      = ''           /* empty string by default for wpa_supplicant */
Language = ''           /* f.i. EN or empty string */
Country  = ''           /* f.i. AT or empty string */
CPU      = ''           /* U for uniprocessor or empty string */
FixPack  = ''           /* */
Description = 'WPA supplicant package for OS/2 - XWLAN Project'
ver_years = '2003-2018'
ver_rev =   ''          /* leave empty as it's taken from version.h */
ver_build = ''          /* empty (default) or numeric value */

outfile  = 'bldlvl.def'

/* some internally used variables */
CrLf     = '0d0a'x;
BldLevelStartTag = '@#';
BldLevelEndTag   = '#@';
Redirection  = '> NUL 2>&1';
fTrace = 0

/* process command line parameters
called with parameter (fTrace) 1 outputs debug messages
called with parameter (fTrace) 2 outputs even more debug info   */
PARSE ARG fTrace

/* limit vendor name */
IF LENGTH(VendorName) > 31 THEN DO
    VendorName = LEFT(VendorName,31)
END

/* get version info from ..\src\common\version.h */
file = '..\src\common\version.h'
IF fTrace > 0 THEN SAY 'ConfigFile='file
IF (lines(file) = 0) THEN SAY '- error:' file 'could not be opened.';

DO WHILE lines(file) > 0
    line = LINEIN(file)
    pos = WORDPOS('VERSION_STR ' , line)
    IF pos > 0 THEN DO
        line=TRANSLATE(line, ' ', '"')
        ver_maj = WORD(line, pos + 1)
        IF fTrace > 1 THEN SAY 'Version='ver_maj
        /* do not process rest of the file */
        LEAVE
    END
END

/* Append years to description string */
Description = Description' 'ver_years

IF WORDLENGTH(ver_rev, 1) > 0 THEN ver_maj = ver_maj'.'ver_rev
IF fTrace > 0 THEN SAY 'Version='ver_maj

/* limit max. build string length */
IF LENGTH(ver_build) > 7 THEN ver_build = LEFT(ver_build,7)

/* compose date and time strings */
datetime = DATE('S')
datetime = INSERT('-', datetime ,6)
datetime = INSERT('-', datetime ,4)
time = TIME()
time = TRANSLATE(time, ' ', ':')
hour = WORD(time, 1)
minu=  WORD(time, 2)
IF LENGTH(hour) < 2 THEN hour = INSERT('0',hour)
IF LENGTH(minu) < 2 THEN minu = INSERT('0',minu)
time = hour':'minu
/* datetime = year'-'month'-'day' 'time */
datetime = datetime' 'time
IF fTrace > 1 THEN SAY 'datetime='datetime

/* compose Feature string (:ASD:EN:US:4b:U:8101) */
Feature=':'ASD':'Language':'Country':'ver_build':'CPU':'FixPack
IF fTrace > 1 THEN  SAY 'Feature='Feature

/* build time stamp und build machine string */
/* date/time have to be 26 chars (leading ' ' required) */
IF LENGTH(BuildMachine) > 11 THEN DO
    BuildMachine = LEFT(BuildMachine, 11)
    END
bldmachlen = LENGTH(BuildMachine)
IF fTrace > 1 THEN SAY 'bldmach='BuildMachine'<-- len='bldmachlen
datimmach = LEFT(datetime, 24)
datimmach = datimmach' 'BuildMachine
IF fTrace > 1 THEN SAY datimmach'<--'

/* bldlevel do not display more than 79 characters */
IF LENGTH(Description) > 79 THEN DO
    Description = LEFT(Description, 79)
    SAY 'Description lenght corrected'
    END


/* FullString = "@#"VendorName':'ver_maj'.'ver_min'#@##1## 'datimmach''Feature'@@  'Description"" */
FullString = "@#"VendorName':'ver_maj'#@##1## 'datimmach''Feature'@@  'Description""
IF fTrace > 0 THEN SAY FullString

/*
 * Replace DESCRIPTION string in .def file
 *
 */

DO 1
  File = outfile;

  IF (STREAM( File, 'C', 'OPEN READ') \= 'READY:') THEN
  DO
     SAY '- error:' File 'could not be opened.';
     rc = ERROR.ACCESS_DENIED;
  END;

  NewFileContents = '';
  DescriptionOkay = FALSE;

  DO WHILE (LINES( File) > 0)
     ThisLine = LINEIN( File);
     IF fTrace > 1 THEN SAY ThisLine

     IF (TRANSLATE( WORD( ThisLine, 1)) = 'DESCRIPTION') THEN
     DO
        IF fTrace > 0 THEN SAY '^--- description found'
        ThisLine = "DESCRIPTION '"FullString"'"
     END;

     /* contents for new file */
     NewFileContents = NewFileContents''CrLf''ThisLine;
     DescriptionOkay = TRUE;
  END;
  IF (DescriptionOkay \= TRUE) THEN NewFileContents = NewFileContents''CrLf''"DESCRIPTION '"FullString"'"


  DO
     /* close and rewrite file */
     rcx = STREAM( File, 'C', 'CLOSE');

     /* write tmp file */
     Contents = SUBSTR( NewFileContents, 3);
     TmpFile = SysTempFilename( VALUE( 'TMP',,OS2ENVIRONMENT)'\bld_temp.???');
     IF (LINEOUT( TmpFile, Contents)) THEN
     DO
        SAY '- error: cannot write' TmpFile;
        EXIT( 99);
     END;
     rcx = LINEOUT( TmpFile);

     /* copy over file */
     '@COPY' TmpFile File Redirection;
     IF (rc \= 0) THEN
     DO
        SAY '- error: cannot write' File;
        EXIT( 99);
     END;
     rcx = SysFileDelete( TmpFile);

  END;

END;

IF (File \= '') THEN
  rcx = STREAM( File, 'C', 'CLOSE');

RETURN( ERROR.NO_ERROR);

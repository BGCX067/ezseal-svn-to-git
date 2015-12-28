/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Jan 15 20:56:39 2011
 */
/* Compiler settings for D:\My Documents\Visual Studio 2008\Projects\ezSeal\ezSeal.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ImySeal = {0xD0D38B3B,0x0A50,0x46E6,{0xA5,0x8F,0x1B,0xE7,0x75,0xCA,0x09,0x5A}};


const IID IID_ICreateSeal = {0xA94858F9,0xF53F,0x4A91,{0xB1,0x91,0xF5,0x81,0x7F,0xDF,0x5E,0x4C}};


const IID LIBID_EZSEALLib = {0x9D06D9E9,0xFC53,0x4729,{0x85,0xD8,0x9C,0xD9,0x09,0xDC,0x44,0x52}};


const CLSID CLSID_mySeal = {0xE548AEC4,0x1B4E,0x4ED3,{0xBD,0x5D,0xDB,0xF4,0x91,0x33,0x4C,0x02}};


const CLSID CLSID_CreateSeal = {0x83027F81,0xFCDB,0x4E61,{0xBF,0xA7,0xA3,0x04,0x8B,0xBA,0xD3,0xD8}};


#ifdef __cplusplus
}
#endif


#ifndef _ACMIS_BLEMISH_EXPORT_H__
#define _ACMIS_BLEMISH_EXPORT_H__

#ifdef LIBACMISBLEMISH_EXPORTS
#define ACMISBLEMISH_API	__declspec(dllexport)
#else
#define ACMISBLEMISH_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_BLEMISH_EXPORT_H__*/

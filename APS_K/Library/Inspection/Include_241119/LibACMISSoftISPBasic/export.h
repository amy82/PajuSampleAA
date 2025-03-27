#ifndef _ACMIS_SOFTISP_BASIC_EXPORT_H__
#define _ACMIS_SOFTISP_BASIC_EXPORT_H__

#ifdef LIBACMISSOFTISPBASIC_EXPORTS
#define ACMISSOFTISPBASIC_API	__declspec(dllexport)
#else
#define ACMISSOFTISPBASIC_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_SOFTISP_BASIC_EXPORT_H__*/

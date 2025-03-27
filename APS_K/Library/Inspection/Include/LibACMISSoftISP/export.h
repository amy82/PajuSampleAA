#ifndef _ACMIS_SOFTISP_EXPORT_H__
#define _ACMIS_SOFTISP_EXPORT_H__

#ifdef LIBACMISSOFTISP_EXPORTS
#define ACMISSOFTISP_API	__declspec(dllexport)
#else
#define ACMISSOFTISP_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_SOFTISP_EXPORT_H__*/

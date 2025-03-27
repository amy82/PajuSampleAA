#ifndef _ACMIS_ETC_EXPORT_H__
#define _ACMIS_ETC_EXPORT_H__

#ifdef LIBACMISETC_EXPORTS
#define ACMISETC_API		__declspec(dllexport)
#else
#define ACMISETC_API		__declspec(dllimport)
#endif


#endif /*_ACMIS_ETC_EXPORT_H__*/

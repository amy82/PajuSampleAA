#ifndef _ACMIS_CERTIFICATION_EXPORT_H__
#define _ACMIS_CERTIFICATION_EXPORT_H__

#ifdef LIBACMISCERTIFICATION_EXPORTS
#define ACMISCERTIFICATION_API	__declspec(dllexport)
#else
#define ACMISCERTIFICATION_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_CERTIFICATION_EXPORT_H__*/

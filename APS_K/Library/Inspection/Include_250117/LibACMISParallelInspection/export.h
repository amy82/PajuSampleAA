#ifndef _ACMIS_PARALLELINSPECTION_EXPORT_H__
#define _ACMIS_PARALLELINSPECTION_EXPORT_H__

#ifdef ACMISPARALLELINSPECTION_EXPORTS
#define ACMISPARALLELINSPECTION_API	__declspec(dllexport)
#else
#define ACMISPARALLELINSPECTION_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_PARALLELINSPECTION_EXPORT_H__*/

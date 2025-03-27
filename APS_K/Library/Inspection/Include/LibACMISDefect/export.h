#ifndef _ACMIS_DEFECT_EXPORT_H__
#define _ACMIS_DEFECT_EXPORT_H__

#ifdef LIBACMISDEFECT_EXPORTS
#define ACMISDEFECT_API	__declspec(dllexport)
#else
#define ACMISDEFECT_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_DEFECT_EXPORT_H__*/

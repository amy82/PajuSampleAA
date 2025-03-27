#ifndef _ACMIS_SHADING_EXPORT_H__
#define _ACMIS_SHADING_EXPORT_H__

#ifdef LIBACMISSHADING_EXPORTS
#define ACMISSHADING_API	__declspec(dllexport)
#else
#define ACMISSHADING_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_SHADING_EXPORT_H__*/

#ifndef _ACMIS_IMAGE_EXPORT_H__
#define _ACMIS_IMAGE_EXPORT_H__

#ifdef LIBACMISIMAGE_EXPORTS
#define ACMISIMAGE_API	__declspec(dllexport)
#else
#define ACMISIMAGE_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_IMAGE_EXPORT_H__*/

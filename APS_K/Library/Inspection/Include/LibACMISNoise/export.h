#ifndef _ACMIS_NOISE_EXPORT_H__
#define _ACMIS_NOISE_EXPORT_H__

#ifdef LIBACMISNOISE_EXPORTS
#define ACMISNOISE_API	__declspec(dllexport)
#else
#define ACMISNOISE_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_NOISE_EXPORT_H__*/

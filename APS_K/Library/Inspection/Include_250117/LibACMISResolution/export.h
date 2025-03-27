/// @mainpage LibACMISResolution
/// @section Introduction
/// - Provide SFR, EIAJ algorithm
/// - Provide SFR, EIAJ Chart Processing
/// @section CREATEINFO Create Information
/// - Team: Optics Software Team in LG Innotek
/// - Date: 2014-02-05
/// @section Copyright
/// - copyright LG Innotek Co., Ltd.

#ifndef _ACMIS_RESOLUTION_EXPORT_H__
#define _ACMIS_RESOLUTION_EXPORT_H__

#ifdef LIBACMISRESOLUTION_EXPORTS
#define ACMISRESOLUTION_API	__declspec(dllexport)
#else
#define ACMISRESOLUTION_API	__declspec(dllimport)
#endif


#endif /*_ACMIS_RESOLUTION_EXPORT_H__*/


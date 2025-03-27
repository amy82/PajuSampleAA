#pragma once

#include "export.h"
#include "ACMISImageDef.h"

// DO NOT INCLUDE HEADER FILE

class ACMISIMAGE_API CACMISSignalNoiseRatioOECF : public CACMISSignalNoiseRatio<TSNROECFSpec>
{
public:
	CACMISSignalNoiseRatioOECF();
	~CACMISSignalNoiseRatioOECF();
};

class ACMISIMAGE_API CACMISPatternNoise : public CACMISSignalNoiseRatio<TPatternNoiseSpec>
{
public:
	CACMISPatternNoise();
	~CACMISPatternNoise();
};

class ACMISIMAGE_API CACMISSignalNoiseRatioBW : public CACMISSignalNoiseRatio<TSNRBWSpec>
{
public:
	CACMISSignalNoiseRatioBW();
	~CACMISSignalNoiseRatioBW();
};


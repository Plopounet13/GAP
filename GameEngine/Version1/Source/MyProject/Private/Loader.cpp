// Fill out your copyright notice in the Description page of Project Settings.
#include "MyProject.h"
#include "CoreMisc.h"
#include "Loader.h"

bool ULoader::Load(struct FFilePath InFilename, int & NbPlatOut, TArray<float>& X, TArray<float>& Y, TArray<float>& Z, TArray<float>& rX, TArray<float>& rY, TArray<float>& rZ, TArray<float>& sX, TArray<float>& sY, TArray<float>& sZ){


	TArray<FString> OutStrings;

	const FString LocalFilePath = FString(FPlatformProcess::BaseDir())+"level.dat";

	bool success=FFileHelper::LoadANSITextFileToStrings( *LocalFilePath, NULL, OutStrings);

	NbPlatOut = OutStrings.Num();

	if (!((NbPlatOut - 1) % 9) || success==false || NbPlatOut<=0) {
		return false;
	}

	int32 index = 0;
	while(index < NbPlatOut){
		X.Add(FCString::Atof(*OutStrings[index]));
		index ++;
		Y.Add(FCString::Atof(*OutStrings[index]));
		index++;
		Z.Add(FCString::Atof(*OutStrings[index]));
		index++;
		rX.Add(FCString::Atof(*OutStrings[index]));
		index++;
		rY.Add(FCString::Atof(*OutStrings[index]));
		index++;
		rZ.Add(FCString::Atof(*OutStrings[index]));
		index++;
		sX.Add(FCString::Atof(*OutStrings[index]));
		index++;
		sY.Add(FCString::Atof(*OutStrings[index]));
		index++;
		sZ.Add(FCString::Atof(*OutStrings[index]));
		index++;
	}

	NbPlatOut = (OutStrings.Num()-1)/9;

	return success;
}

// Fill out your copyright notice in the Description page of Project Settings.
#include "MyProject.h"
#include "CoreMisc.h"
#include "Loader.h"

bool ULoader::Load(
	FString InFilename, 
	int & NbPlatOut, 
	TArray<float>& X,
	TArray<float>& Y, 
	TArray<float>& Z, 
	TArray<float>& rX, 
	TArray<float>& rY, 
	TArray<float>& rZ, 
	TArray<float>& sX, 
	TArray<float>& sY, 
	TArray<float>& sZ, 
	TArray<int>& Plat_Type,
	TArray<int>& Begin4D,
	TArray<float>& Array_4D){


	TArray<FString> OutStrings;

	FString LocalFilePath = (FPaths::GameDir() + InFilename);

	bool success=FFileHelper::LoadANSITextFileToStrings(*LocalFilePath, NULL, OutStrings);

	NbPlatOut = 0;
	int32 index = 0;
	Begin4D.Add(0);
	for (NbPlatOut = 0; index < OutStrings.Num(); NbPlatOut++) {
		Plat_Type.Add(FCString::Atoi(*OutStrings[index]));
		index++;

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

		int32 Nb4D=FCString::Atoi(*OutStrings[index]);
		index++;

		int32 index_4D;
		for (index_4D = 0; index_4D < Nb4D; index_4D++) {
			Array_4D.Add(FCString::Atof(*OutStrings[index]));
			index++;
		}

		Begin4D.Add(Array_4D.Num());
	}

	NbPlatOut--;

	return success;
}

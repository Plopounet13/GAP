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
	TArray<float>& appear,
	TArray<float>& disappear,
	TArray<float>& full_4d_start,
	TArray<float>& full_4d_end){
	//IMPORTANT !!!!!
	const int nb_param = 13;

	TArray<FString> OutStrings;

	FString LocalFilePath = (FPaths::GameDir() + InFilename);

	bool success=FFileHelper::LoadANSITextFileToStrings(*LocalFilePath, NULL, OutStrings);

	NbPlatOut = OutStrings.Num();

	if ( (NbPlatOut% nb_param != 0) || success==false || NbPlatOut<=0) {
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
		
		appear.Add(FCString::Atof(*OutStrings[index]));
		index++;
		disappear.Add(FCString::Atof(*OutStrings[index]));
		index++;
		full_4d_start.Add(FCString::Atof(*OutStrings[index]));
		index++;
		full_4d_end.Add(FCString::Atof(*OutStrings[index]));
		index++;
	}

	NbPlatOut = (OutStrings.Num()-1)/nb_param;

	return success;
}

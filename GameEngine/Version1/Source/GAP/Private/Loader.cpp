// Fill out your copyright notice in the Description page of Project Settings.
#include "GAP.h"
#include "CoreMisc.h"
#include "Loader.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, text)
//debug print

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
	//print(LocalFilePath);

	NbPlatOut = 0;
	int32 index = 0;
	Begin4D.Add(0);
	for (NbPlatOut = 0; index < OutStrings.Num(); NbPlatOut++) {
		Plat_Type.Add(FCString::Atoi(*OutStrings[index]));
		++index;

		X.Add(FCString::Atof(*OutStrings[index]));
		++index;
		Y.Add(FCString::Atof(*OutStrings[index]));
		++index;
		Z.Add(FCString::Atof(*OutStrings[index]));
		++index;

		rX.Add(FCString::Atof(*OutStrings[index]));
		++index;
		rY.Add(FCString::Atof(*OutStrings[index]));
		++index;
		rZ.Add(FCString::Atof(*OutStrings[index]));
		++index;

		sX.Add(FCString::Atof(*OutStrings[index]));
		++index;
		sY.Add(FCString::Atof(*OutStrings[index]));
		++index;
		sZ.Add(FCString::Atof(*OutStrings[index]));
		++index;

		int32 Nb4D=FCString::Atoi(*OutStrings[index]);
		++index;

		int32 index_4D;
		for (index_4D = 0; index_4D < Nb4D; index_4D++) {
			Array_4D.Add(FCString::Atof(*OutStrings[index]));
			++index;
		}

		Begin4D.Add(Array_4D.Num());
	}

	--NbPlatOut;

	return success;
}


void ULoader::interpol(const TArray<float> & Values, const TArray<float> & Index4D, float Pos_4D, float & Output) {
	int i = 0;
	if (Pos_4D >= 0 && Pos_4D <= MAX4D)
		print("4D from interpol outside [0,1000]");
	while (i<Index4D.Num() && Index4D[i]<Pos_4D) {
		++i;
	}
	float p1, p2, v1, v2;
	if (i == 0 || i == Index4D.Num()) {
		p1 = Index4D.Last() - MAX4D;
		p2 = Index4D[0];
		v1 = Values.Last();
		v2 = Values[0];
	}
	else {
		p1 = Index4D[i - 1];
		p2 = Index4D[i];
		v1 = Values[i - 1];
		v2 = Values[i];
	}

	Output = ((p2 - Pos_4D)*v1 + (Pos_4D - p1)*v2) / (p2 - p1);
}

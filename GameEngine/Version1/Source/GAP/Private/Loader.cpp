// Fill out your copyright notice in the Description page of Project Settings.
#include "GAP.h"
#include "CoreMisc.h"
#include "Loader.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, text)
//debug print

bool ULoader::Load(FString InFilename,
				   int & NbPlatOut,
				   TArray<int>& plat_type,
				   TArray<float>& random_number,
				   TArray<FVector>& pos_actor,
				   TArray<FRotator>& rot_actor,
				   TArray<FVector>& scale_actor,
				   TArray<int>& nb_exit,
				   TArray<int>& begin_exit,
				   TArray<FVector>& vect_exit,
				   TArray<int>& begin_4D,
				   TArray<float>& indice_4D,
				   TArray<FVector>& pos_4D,
				   TArray<FRotator>& rot_4D,
				   TArray<FVector>& scale_4D
				   ){


	TArray<FString> in_strings;

	FString LocalFilePath = (FPaths::GameDir() + InFilename);

	bool success=FFileHelper::LoadANSITextFileToStrings(*LocalFilePath, NULL, in_strings);
	//print(LocalFilePath);

	int32 index = 0;
	begin_exit.Add(0);
	begin_4D.Add(0);
	NbPlatOut = 0;
	while (index < in_strings.Num()){
		++NbPlatOut;
		float x, y, z;
		
		plat_type.Add(FCString::Atoi(*in_strings[index]));
		++index;
		
		random_number.Add(FCString::Atoi(*in_strings[index]));
		++index;
		
		x = FCString::Atof(*in_strings[index]);
		++index;
		y = FCString::Atof(*in_strings[index]);
		++index;
		z = FCString::Atof(*in_strings[index]);
		++index;
		pos_actor.Emplace(x, y, z);
		
		x = FCString::Atof(*in_strings[index]);
		++index;
		y = FCString::Atof(*in_strings[index]);
		++index;
		z = FCString::Atof(*in_strings[index]);
		++index;
		rot_actor.Emplace(x, y, z);
		
		x = FCString::Atof(*in_strings[index]);
		++index;
		y = FCString::Atof(*in_strings[index]);
		++index;
		z = FCString::Atof(*in_strings[index]);
		++index;
		scale_actor.Emplace(x, y, z);

		nb_exit.Add(FCString::Atoi(*in_strings[index]));
		++index;
		
		int32 index_exit;
		for (index_exit=0; index_exit<nb_exit.Last(); ++index_exit){
			x = FCString::Atof(*in_strings[index]);
			++index;
			y = FCString::Atof(*in_strings[index]);
			++index;
			z = FCString::Atof(*in_strings[index]);
			++index;
			vect_exit.Emplace(x, y, z);
		}
		begin_exit.Add(vect_exit.Num());
		
		int32 nb_4D=FCString::Atoi(*in_strings[index]);
		++index;

		int32 index_4D;
		for (index_4D = 0; index_4D < nb_4D; index_4D++) {
			x = FCString::Atof(*in_strings[index]);
			++index;
			y = FCString::Atof(*in_strings[index]);
			++index;
			z = FCString::Atof(*in_strings[index]);
			++index;
			pos_4D.Emplace(x, y, z);
			
			indice_4D.Add(FCString::Atof(*in_strings[index]));
			++index;
			
			x = FCString::Atof(*in_strings[index]);
			++index;
			y = FCString::Atof(*in_strings[index]);
			++index;
			z = FCString::Atof(*in_strings[index]);
			++index;
			rot_4D.Emplace(x, y, z);
			
			x = FCString::Atof(*in_strings[index]);
			++index;
			y = FCString::Atof(*in_strings[index]);
			++index;
			z = FCString::Atof(*in_strings[index]);
			++index;
			scale_4D.Emplace(x, y, z);
		}

		begin_4D.Add(indice_4D.Num());
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

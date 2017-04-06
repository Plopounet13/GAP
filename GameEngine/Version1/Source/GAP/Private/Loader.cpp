// Fill out your copyright notice in the Description page of Project Settings.
#include "GAP.h"
#include "CoreMisc.h"
#include "Loader.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, text)
#define safe_pp(var, max, str); if(var<max){++var;}else{print(str);return false;} 
//debug print

bool ULoader::Load(FString InFilename,
				   int & NbPlatOut,
				   TArray<int>& plat_type,
				   TArray<float>& random_number,
				   TArray<FVector>& pos_actor,
				   TArray<float>& pos_4D_start,
				   TArray<FRotator>& rot_actor,
				   TArray<FVector>& scale_actor,
				   TArray<int>& nb_exit,
				   TArray<int>& begin_exit,
				   TArray<FVector>& vect_exit,
				   TArray<float>& vect_exit_4D,
				   TArray<int>& begin_4D,
				   TArray<float>& indice_4D,
				   TArray<FVector>& pos_4D,
				   TArray<FRotator>& rot_4D,
				   TArray<FVector>& scale_4D
				   ){


	TArray<FString> in_strings;

	FString LocalFilePath = (FPaths::GameDir() + "/Levels/" + InFilename);

	bool success;



	success= FFileHelper::LoadANSITextFileToStrings(*LocalFilePath, NULL, in_strings);

	int32 index = - 1;
	begin_exit.Add(0);
	begin_4D.Add(0);
	NbPlatOut = 0;
	int32 num = in_strings.Num()-1;
	while (index < num){
		++NbPlatOut;
		float x, y, z;
		safe_pp(index, num, FString::FromInt(__LINE__));
		plat_type.Add(FCString::Atoi(*in_strings[index]));

		safe_pp(index,num, FString::FromInt(__LINE__));
		random_number.Add(FCString::Atoi(*in_strings[index]));
			
		safe_pp(index,num, FString::FromInt(__LINE__));
		x = FCString::Atof(*in_strings[index]);
		safe_pp(index,num, FString::FromInt(__LINE__));
		y = FCString::Atof(*in_strings[index]);
		safe_pp(index,num, FString::FromInt(__LINE__));
		z = FCString::Atof(*in_strings[index]);
		pos_actor.Emplace(x, y, z);
			

		safe_pp(index, num, FString::FromInt(__LINE__));
		x = FCString::Atof(*in_strings[index]);
		pos_4D_start.Emplace(x);
			

		safe_pp(index, num, FString::FromInt(__LINE__));
		x = FCString::Atof(*in_strings[index]);
		safe_pp(index,num, FString::FromInt(__LINE__));
		y = FCString::Atof(*in_strings[index]);
		safe_pp(index,num, FString::FromInt(__LINE__));
		z = FCString::Atof(*in_strings[index]);
		rot_actor.Emplace(y, z, x);
			

		safe_pp(index, num, FString::FromInt(__LINE__));
		x = FCString::Atof(*in_strings[index]);
		safe_pp(index,num, FString::FromInt(__LINE__));
		y = FCString::Atof(*in_strings[index]);
		safe_pp(index,num, FString::FromInt(__LINE__));
		z = FCString::Atof(*in_strings[index]);
		scale_actor.Emplace(x, y, z);

		safe_pp(index, num, FString::FromInt(__LINE__));
		nb_exit.Add(FCString::Atoi(*in_strings[index]));
			
		
		int32 index_exit;
		for (index_exit=0; index_exit<nb_exit.Last(); ++index_exit){
			safe_pp(index, num, FString::FromInt(__LINE__));
			x = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			y = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			z = FCString::Atof(*in_strings[index]);
			vect_exit.Emplace(x, y, z);

			safe_pp(index, num, FString::FromInt(__LINE__));
			x = FCString::Atof(*in_strings[index]);
			vect_exit_4D.Add(x);
		}
		begin_exit.Add(vect_exit.Num());

		safe_pp(index, num, FString::FromInt(__LINE__));
		int32 nb_4D=FCString::Atoi(*in_strings[index]);

		int32 index_4D;
		for (index_4D = 0; index_4D < nb_4D; ++index_4D) {
			safe_pp(index, num, FString::FromInt(__LINE__));
			x = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			y = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			z = FCString::Atof(*in_strings[index]);
			pos_4D.Emplace(x, y, z);
				

			safe_pp(index, num, FString::FromInt(__LINE__));
			indice_4D.Add(FCString::Atof(*in_strings[index]));
				
			safe_pp(index,num, FString::FromInt(__LINE__));
			x = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			y = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			z = FCString::Atof(*in_strings[index]);
			rot_4D.Emplace(y, z, x);
				
			safe_pp(index, num, FString::FromInt(__LINE__));
			x = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			y = FCString::Atof(*in_strings[index]);
			safe_pp(index,num, FString::FromInt(__LINE__));
			z = FCString::Atof(*in_strings[index]);

			scale_4D.Emplace(x, y, z);
		}

		begin_4D.Add(indice_4D.Num());
	}

	--NbPlatOut;

	return success;
}


void ULoader::interpolate_vector(const TArray<FVector> & Values, const TArray<float> & Index4D, float Pos_4D, FVector & Output) {
	int i = 0;
	if (Pos_4D < 0 || Pos_4D > MAX4D)
		print("4D from interpol outside [0,1000]");
	while (i<Index4D.Num() && Index4D[i]<Pos_4D) {
		++i;
	}
	float p1, p2;
	FVector v1, v2;
	if (i == 0 || i == Index4D.Num()) {
		p1 = Index4D.Last() - MAX4D;
		p2 = Index4D[0];
		v1 = Values.Last();
		v2 = Values[0];
		if (i == Index4D.Num())
			Pos_4D -= MAX4D;
	}
	else {
		p1 = Index4D[i - 1];
		p2 = Index4D[i];
		v1 = Values[i - 1];
		v2 = Values[i];
	}

	Output = ((p2 - Pos_4D)*v1 + (Pos_4D - p1)*v2) / (p2 - p1);
}

void ULoader::interpolate_rotator(const TArray<FRotator> & Values, const TArray<float> & Index4D, float Pos_4D, FRotator & Output) {
	int i = 0;
	if (Pos_4D < 0 || Pos_4D > MAX4D)
		print("4D from interpol outside [0,1000]");
	while (i<Index4D.Num() && Index4D[i]<Pos_4D) {
		++i;
	}
	float p1, p2;
	FRotator v1, v2;
	if (i == 0 || i == Index4D.Num()) {
		p1 = Index4D.Last() - MAX4D;
		p2 = Index4D[0];
		v1 = Values.Last();
		v2 = Values[0];
		if (i == Index4D.Num())
			Pos_4D -= MAX4D;
	}
	else {
		p1 = Index4D[i - 1];
		p2 = Index4D[i];
		v1 = Values[i - 1];
		v2 = Values[i];
	}

	Output = ((p2 - Pos_4D)*v1 + (Pos_4D - p1)*v2) * (1/(p2 - p1));
}

bool ULoader::Scan(TArray<FString> &LevelList) {

	FString path = FPaths::GameDir();

	if (path.Len() < 1) return false;

	FPaths::NormalizeDirectoryName(path);

	IFileManager& FileManager = IFileManager::Get();
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	path = path + "/Levels/";
	if (!PlatformFile.DirectoryExists(*path))
	{
		PlatformFile.CreateDirectory(*path);

		if (!PlatformFile.DirectoryExists(*path))
		{
			return false;
		}
	}

	FString FinalPath = path + "*.dat";
	FileManager.FindFiles(LevelList, *FinalPath, true, false);

	int i;
	for (i = 0; i < LevelList.Num(); i++) {
		LevelList[i].RemoveFromEnd(".dat", ESearchCase::IgnoreCase);
	}

	return true;
}

bool ULoader::LaunchGenerator() {
	FPlatformProcess::CreateProc(TEXT("C:\\Windows\\notepad.exe"), nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
	print("plop");
	return true;
}

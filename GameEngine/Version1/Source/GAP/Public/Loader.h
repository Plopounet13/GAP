// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMisc.h"
#include "Loader.generated.h"

/**
 *
 */
#define MAX4D 1000

UCLASS()
class GAP_API ULoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "LevelLoader")
	static bool Load(FString InFilename,
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
			);

	UFUNCTION(BlueprintCallable, Category = "LevelLoader")
	static void interpolate_vector(const TArray<FVector> & Values, const TArray<float> & Index4D, float Pos_4D, FVector & Output);

	UFUNCTION(BlueprintCallable, Category = "LevelLoader")
	static void interpolate_rotator(const TArray<FRotator> & Values, const TArray<float> & Index4D, float Pos_4D, FRotator & Output);


	
};

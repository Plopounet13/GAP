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
		static bool Load(FString InFilename, int & NbPlatOut, TArray<float> &X, TArray<float> &Y, TArray<float> &Z,
			TArray<float> &rX, TArray<float> &rY, TArray<float> &rZ,
			TArray<float> &sX, TArray<float> &sY, TArray<float> &sZ,
			TArray<int > &Plat_Type, TArray<int> &Begin4D, TArray<float> &Array_4D);

		UFUNCTION(BlueprintCallable, Category = "LevelLoader")
		static void interpol(const TArray<float> & Values, const TArray<float> & Index4D, float Pos_4D, float & Output);
	
};

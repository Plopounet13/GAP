// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMisc.h"
#include "Loader.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ULoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintCallable, Category = "LevelLoader")
		static bool Load(struct FFilePath InFilename, int & NbPlatOut, TArray<float> &X, TArray<float> &Y, TArray<float> &Z,
			TArray<float> &rX, TArray<float> &rY, TArray<float> &rZ,
			TArray<float> &sX, TArray<float> &sY, TArray<float> &sZ);
	
};

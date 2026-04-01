// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPS_Character.generated.h"

UCLASS()
class STUDY_API ANPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ANPS_Character();

protected:
	virtual void BeginPlay() override;
};

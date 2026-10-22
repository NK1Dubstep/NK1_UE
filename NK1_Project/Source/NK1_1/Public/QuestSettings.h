// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestSettings.generated.h"

class UQuestCondition;

/**
 *
 */
UCLASS()
class NK1_1_API UQuestSettings : public UDataAsset
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(Instanced, EditAnywhere)
	TArray<TObjectPtr<UQuestCondition>> StartConditionsQS;

	UPROPERTY(Instanced, EditAnywhere)
	TArray<TObjectPtr<UQuestCondition>> EndConditionsQS;

	UPROPERTY()
	TArray<TSubclassOf<UQuestCondition>> StartConditions_DEPRECATED;

	UPROPERTY()
	TArray<TSubclassOf<UQuestCondition>> EndConditions_DEPRECATED;

	void PostLoad() override;
};

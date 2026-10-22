// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "TriggerVolume_QuestCondition.generated.h"

/**
 *
 */
UCLASS()
class NK1_1_API UTriggerVolume_QuestCondition : public UQuestCondition
{
	GENERATED_BODY()

  public:
	void StartCondition() override;
	void StopCondition() override;

	UFUNCTION()
	void VolumeTrigger(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	FName OtherTag;

	UPROPERTY(EditAnywhere)
	bool bStartOnEnter{true};
};

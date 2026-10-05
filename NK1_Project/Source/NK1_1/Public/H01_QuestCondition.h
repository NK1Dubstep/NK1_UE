// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "H01_QuestCondition.generated.h"

/**
 * 
 */
UCLASS()
class NK1_1_API UH01_QuestCondition : public UQuestCondition
{
	GENERATED_BODY()

	public:
	void StartCondition() override;
	void StopCondition() override;
	
};

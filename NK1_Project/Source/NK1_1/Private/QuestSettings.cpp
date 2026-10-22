// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSettings.h"
#include "QuestCondition.h"
#include "QuestLog.h"

void UQuestSettings::PostLoad()
{
	Super::PostLoad();

	if (!StartConditions_DEPRECATED.IsEmpty())
	{
		auto oldNum = StartConditionsQS.Num();

		for (const TSubclassOf<UQuestCondition>& ConditionTemplate : StartConditions_DEPRECATED)
		{
			if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
			{
				return;
			}
			UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
			if (!QuestCondition)
			{
				UE_LOG(LogQuest, Warning, TEXT("QuestSettings: Quest start condition new object fail"));
				continue;
			}
			StartConditionsQS.Add(QuestCondition);
		}
		UE_LOG(LogQuest, Log, TEXT("QuestSettings: %i deprecated start conditions added"), StartConditionsQS.Num() - oldNum);
		StartConditions_DEPRECATED.Empty();
	}

	if (!EndConditions_DEPRECATED.IsEmpty())
	{
		auto oldNum = EndConditionsQS.Num();

		for (const TSubclassOf<UQuestCondition>& ConditionTemplate : EndConditions_DEPRECATED)
		{
			if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
			{
				return;
			}
			UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
			if (!QuestCondition)
			{
				UE_LOG(LogQuest, Warning, TEXT("QuestSettings: Quest end condition new object fail"));
				continue;
			}
			EndConditionsQS.Add(QuestCondition);
		}
		UE_LOG(LogQuest, Log, TEXT("QuestSettings: %i deprecated end conditions added"), EndConditionsQS.Num() - oldNum);
		EndConditions_DEPRECATED.Empty();
	}
}

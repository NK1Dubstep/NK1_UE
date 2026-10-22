// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestCondition.h"
#include "QuestLog.h"

void UQuestCondition::Complete()
{
	UE_LOG(LogQuest, Log, TEXT("Condition %p [%s] of class %s completed"), this, *GetNameSafe(this), *GetNameSafe(GetClass()));
	bCompleted = true;
	OnQuestConditionCompleted.Broadcast();
}

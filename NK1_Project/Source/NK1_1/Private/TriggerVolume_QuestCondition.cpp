// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerVolume_QuestCondition.h"
#include "Quest.h"
#include "QuestLog.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
	AQuest* Quest = Cast<AQuest>(GetOuter());
	if (!Quest)
	{
		UE_LOG(LogQuest, Error, TEXT("UTriggerVolume_QuestCondition: Quest, not %s must be outer"), *GetNameSafe(GetOuter()));
		return;
	}

	if (bStartOnEnter)
		Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
	else
		Quest->OnActorEndOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
	UE_LOG(LogQuest, Log, TEXT("UTriggerVolume_QuestCondition: %p Started"), this);
}

void UTriggerVolume_QuestCondition::StopCondition()
{
	AQuest* Quest = Cast<AQuest>(GetOuter());
	if (!Quest)
	{
		UE_LOG(LogQuest, Error, TEXT("UTriggerVolume_QuestCondition: Quest, not %s must be outer"), *GetNameSafe(GetOuter()));
		return;
	}

	if (bStartOnEnter)
		Quest->OnActorBeginOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
	else
		Quest->OnActorEndOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
	UE_LOG(LogQuest, Log, TEXT("UTriggerVolume_QuestCondition: %p Ended"), this);
}

void UTriggerVolume_QuestCondition::VolumeTrigger(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogQuest, Log, TEXT("UTriggerVolume_QuestCondition: Overlap trigger: overlapped: %p [%s], other: %p [%s]"),
		OverlappedActor, *GetNameSafe(OverlappedActor), OtherActor, *GetNameSafe(OtherActor));
	if (OtherActor && OtherActor->ActorHasTag(OtherTag))
	{
		Complete();
	}
}

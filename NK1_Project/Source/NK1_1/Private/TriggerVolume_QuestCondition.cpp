// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_QuestCondition.h"
#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
  AQuest *Quest = Cast<AQuest>(GetOuter());

  if (bStartOnEnter)
    Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
  else
    Quest->OnActorEndOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
}

void UTriggerVolume_QuestCondition::StopCondition()
{
  AQuest *Quest = Cast<AQuest>(GetOuter());

  if (bStartOnEnter)
    Quest->OnActorBeginOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
  else
    Quest->OnActorEndOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::VolumeTrigger);
}

void UTriggerVolume_QuestCondition::VolumeTrigger(AActor *OverlappedActor, AActor *OtherActor)
{
  if (OtherActor->ActorHasTag(OtherTag))
  {
    Complete();
    StopCondition();
  }
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest.h"

#include "GameFramework/GameModeBase.h"
#include "LongQuestSystemComponent.h"
#include "QuestCondition.h"
#include "QuestSettings.h"
#include "QuestLog.h"

// Sets default values
AQuest::AQuest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();

	if (ULongQuestSystemComponent* QuestComponent = GetWorld()->GetAuthGameMode()->GetComponentByClass<ULongQuestSystemComponent>())
	{
		QuestComponent->RegisterQuest(this);
	}
	else
	{
	  UE_LOG(LogQuest, Error, TEXT("Quest: Quest system component not found"));
	}

	if (!QuestSettings)
	{
	  UE_LOG(LogQuest, Error, TEXT("Quest: !QuestSettings"));
	  return;
	}

	for (const UQuestCondition *ConditionTemplate : QuestSettings->StartConditionsQS)
	{

		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			return;
		}

		UQuestCondition* QuestCondition = DuplicateObject<UQuestCondition>(ConditionTemplate, this);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
		StartConditions.Add(QuestCondition);
	}
}

// Called every frame
void AQuest::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AQuest::UpdateStartStatus()
{
	for (UQuestCondition* cond : StartConditions)
	{
		if (!ensure(cond))
		{
			return;
		}
		if (!cond->IsCompleted())
		{
			return;
		}
	}

	SetQuestStatus(EQuestStatus::Started);

	for (UQuestCondition* cond : StartConditions)
	{
		cond->StopCondition();
		cond->OnQuestConditionCompleted.RemoveAll(this);
	}

	for (const UQuestCondition *ConditionTemplate : QuestSettings->EndConditionsQS)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			return;
		}

		UQuestCondition* QuestCondition = DuplicateObject<UQuestCondition>(ConditionTemplate, this);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
		EndConditions.Add(QuestCondition);
	}
}

void AQuest::UpdateEndStatus()
{
	for (UQuestCondition* cond : EndConditions)
	{
		if (!ensure(cond))
		{
			return;
		}
		if (!cond->IsCompleted())
		{
			return;
		}
	}

	SetQuestStatus(EQuestStatus::Completed);

	for (UQuestCondition* cond : EndConditions)
	{
		cond->StopCondition();
		cond->OnQuestConditionCompleted.RemoveAll(this);
	}
}

void AQuest::SetQuestStatus(const EQuestStatus NewQuestStatus)
{
	if (QuestStatus == NewQuestStatus)
		return;
	UE_LOG(LogQuest, Log, TEXT("Quest %p [%s]: changing status %s -> %s"), this, *GetNameSafe(this),
	  *UEnum::GetValueAsString(QuestStatus), *UEnum::GetValueAsString(NewQuestStatus));
	QuestStatus = NewQuestStatus;
	OnQuestStatusChanged.Broadcast(this, NewQuestStatus);
}

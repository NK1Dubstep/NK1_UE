// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "QuestSettings.h"
#include "QuestCondition.h"
#include "LongQuestSystemComponent.h"
#include "GameFramework/GameModeBase.h"

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

	if (ULongQuestSystemComponent *QuestComponent = GetWorld()->GetAuthGameMode()->GetComponentByClass<ULongQuestSystemComponent>())
	{
		QuestComponent->RegisterQuest(this);
	}

	for (const TSubclassOf<UQuestCondition> &ConditionTemplate : QuestSettings->StartConditions)
	{

		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			return;
		}

		UQuestCondition *QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
		StartConditions.Add(QuestCondition);
	}
	
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuest::UpdateStartStatus()
{
	for (UQuestCondition *cond : StartConditions)
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

	for (const TSubclassOf<UQuestCondition> &ConditionTemplate : QuestSettings->EndConditions)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
		{
			return;
		}

		UQuestCondition *QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
		EndConditions.Add(QuestCondition);
	}

}

void AQuest::UpdateEndStatus()
{
	for (UQuestCondition *cond : EndConditions)
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
}

void AQuest::SetQuestStatus(const EQuestStatus NewQuestStatus)
{
	if (QuestStatus == NewQuestStatus)
		return;
	QuestStatus = NewQuestStatus;
	OnSomeQuestStatusChanged.Broadcast(this, NewQuestStatus);
}

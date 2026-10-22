// Fill out your copyright notice in the Description page of Project Settings.

#include "LongQuestSystemComponent.h"
#include "Quest.h"
#include "QuestLog.h"

#include "EngineUtils.h"

// Sets default values for this component's properties
ULongQuestSystemComponent::ULongQuestSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULongQuestSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const TSubclassOf<AQuest>& QuestClass : Quests)
	{
		auto ptr = GetWorld()->SpawnActor<AQuest>(QuestClass);
		if (!ptr)
		{
			UE_LOG(LogQuest, Warning, TEXT("LongQuestSystemComponent: Spawn quest fail"))
			continue;
		}
		UE_LOG(LogQuest, Log, TEXT("LongQuestSystemComponent: Spawn quest success %p [%s]"), ptr, *GetNameSafe(ptr));
	}
}

void ULongQuestSystemComponent::GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests)
{
	for (AQuest* q : ActiveQuests)
	{
		auto status = q->GetQuestStatus();
		if (status == EQuestStatus::Started || status == EQuestStatus::Completed)
		{
			OutQuests.Add(q);
		}
	}
}

// Called every frame
void ULongQuestSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULongQuestSystemComponent::RegisterQuest(AQuest* NewQuest)
{
	ActiveQuests.AddUnique(NewQuest);
	UE_LOG(LogQuest, Log, TEXT("LongQuestSystemComponent: quest %p [%s] registered"), NewQuest, *GetNameSafe(NewQuest));
}

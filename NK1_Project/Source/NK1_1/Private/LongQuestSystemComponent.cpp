// Fill out your copyright notice in the Description page of Project Settings.


#include "LongQuestSystemComponent.h"
#include "Quest.h"

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

for (TActorIterator<AQuest> it(GetWorld(), AQuest::StaticClass()); it; ++it)
{
    ActiveQuests.AddUnique(*it);
}

	for (const TSubclassOf<AQuest> &QuestClass : Quests)
	{
		AQuest *Quest = GetWorld()->SpawnActor<AQuest>(QuestClass);
		ActiveQuests.Add(Quest);
	}
	
}

void ULongQuestSystemComponent::GetActiveAndStartedQuests(TArray<AQuest *> &OutQuests)
{
	for (AQuest *q: ActiveQuests)
	{
		if (q->GetQuestStatus() == EQuestStatus::Started)
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

void ULongQuestSystemComponent::RegisterQuest(AQuest *NewQuest)
{
	ActiveQuests.AddUnique(NewQuest);
}

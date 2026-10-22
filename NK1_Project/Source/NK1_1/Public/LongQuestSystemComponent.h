// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "LongQuestSystemComponent.generated.h"

class AQuest;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NK1_1_API ULongQuestSystemComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	ULongQuestSystemComponent();

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) void GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests);

	void RegisterQuest(AQuest* NewQuest);

  protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AQuest>> Quests;
	UPROPERTY()
	TArray<AQuest*> ActiveQuests;
};

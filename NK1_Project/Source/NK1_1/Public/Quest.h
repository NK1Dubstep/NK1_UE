// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

class AQuest;
class UQuestSettings;
class UQuestCondition;

UENUM()
enum class EQuestStatus : uint8
{
	WaitingForStart,
	Started,
	Completed
};

// Delegate signature
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSomeQuestStatusChanged, AQuest * /* Quest */, EQuestStatus /* NewQuestStatus */)

UCLASS()
class NK1_1_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateStartStatus();
	void UpdateEndStatus();

	EQuestStatus GetQuestStatus() const noexcept { return QuestStatus; }

	FOnSomeQuestStatusChanged OnSomeQuestStatusChanged;

protected:

	UPROPERTY(EditAnywhere) TObjectPtr<UQuestSettings> QuestSettings;

	UPROPERTY()
	TArray<UQuestCondition*> StartConditions;

	UPROPERTY()
	TArray<UQuestCondition*> EndConditions;

	UPROPERTY(BlueprintReadOnly)
	EQuestStatus QuestStatus{EQuestStatus::WaitingForStart};

	void SetQuestStatus(EQuestStatus NewQuestStatus);



};

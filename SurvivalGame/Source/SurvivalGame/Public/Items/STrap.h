// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SCharacter.h"
#include "STrap.generated.h"

UENUM()
enum class ETrapState
{
	Placed,
	Set,
	Sprung
};

UCLASS(ABSTRACT, Blueprintable)
class SURVIVALGAME_API ASTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTrap();


	UPROPERTY()
		USceneComponent* OurVisibleComponent;

	UPROPERTY()
		UStaticMeshComponent* SphereVisual;

	UPROPERTY()
		UMaterial* trapColour;

	UMaterialInstanceDynamic* MatDynamic;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Create the the containers for the base trap class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Properties")
		bool isActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Properties")
		bool wasSet;

	UPROPERTY(EditAnywhere, Category = "Trap Properties")
		float trapRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Properties")
		float trapState;

	//Function to be called on overlap
	UFUNCTION()
		void OnOverlap(AActor* OtherActor);

	//Function to be called on overlap End
	UFUNCTION()
		void OnOverlapEnd(AActor* OtherActor);

	//Function to Set the trap
	UFUNCTION(BlueprintCallable, Category = "Trap Commands")
		virtual void SetTrap(AActor* OtherActor);

	TSubclassOf<class ATrap> TrapClass;

	
	
};

// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SUsableActor.h"
#include "SCharacter.h"
#include "STrap.generated.h"

UENUM()
enum class ETrapState : uint8
{
	Placed,
	Set,
	Sprung
};

UCLASS(ABSTRACT, Blueprintable)
class SURVIVALGAME_API ASTrap : public ASUsableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTrap(const FObjectInitializer& ObjectInitializer);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/* Called when player interacts with object */
	virtual void OnUsed(APawn* InstigatorPawn);

	UPROPERTY(EditAnywhere, Category = "Trap Properties")
		float trapRadius;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Trap Properties")
		ETrapState trapState;

	UPROPERTY(Replicated)
		UMaterialInstanceDynamic* MatDynamic;

	UPROPERTY(ReplicatedUsing = OnRep_Flag)
		uint32 bFlag : 1;

	//Function to be called on overlap
	UFUNCTION()
		void OnOverlap(AActor* OtherActor);

	//Function to be called on overlap End
	UFUNCTION()
		void OnOverlapEnd(AActor* OtherActor);

	//Function to Set the trap
	virtual void SetTrap(AActor* OtherActor);

	virtual void UpdateTrapState(ETrapState newState);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUpdateTrapState(ETrapState newState);

	virtual void ServerUpdateTrapState_Implementation(ETrapState newState);

	virtual bool ServerUpdateTrapState_Validate(ETrapState newState);

	TSubclassOf<class ATrap> TrapClass;

	UFUNCTION()
		void OnRep_Flag();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	
};

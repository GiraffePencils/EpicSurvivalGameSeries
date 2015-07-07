// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SurvivalGame.h"
//#include "UnrealNetwork.h"
#include "STrap.h"


// Sets default values
ASTrap::ASTrap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set all the Default values

	trapRadius = 40.0f;

	//Delegate declaration.
	OnActorBeginOverlap.AddDynamic(this, &ASTrap::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASTrap::OnOverlapEnd);

	
	bReplicates = true;

}

// Called when the game starts or when spawned
void ASTrap::BeginPlay()
{
	Super::BeginPlay();

	if (MeshComp)
	{
		MatDynamic = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
	}
	
	UpdateTrapState(ETrapState::Placed);


}
void ASTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTrap::OnUsed(APawn* InstigatorPawn)
{
	Super::OnUsed(InstigatorPawn);

		SetTrap(InstigatorPawn);
}

//Do something with the other actor.
void ASTrap::OnOverlap(AActor* OtherActor)
{
	if (trapState==ETrapState::Set)
	{
		UpdateTrapState(ETrapState::Sprung);
	}

}

void ASTrap::OnOverlapEnd(AActor* OtherActor)
{


}

void ASTrap::SetTrap(AActor* OtherActor)
{

	if (trapState == ETrapState::Placed)
	{
		UpdateTrapState(ETrapState::Set);
	}
	
}

void ASTrap::UpdateTrapState(ETrapState newState)
{
	trapState = newState;

	switch (trapState)
	{
	case ETrapState::Placed:
		if (MatDynamic)
		{
			GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Blue, (Role == ROLE_Authority) ? TEXT("Auth") : TEXT("Client"));
			MatDynamic->SetVectorParameterValue("InputColor", FVector(0.0f, 0.0f, 1.0f));
		}
		break;
	case ETrapState::Set:
		if (MatDynamic)
		{
			GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Blue, (Role == ROLE_Authority) ? TEXT("Auth") : TEXT("Client"));
			MatDynamic->SetVectorParameterValue("InputColor", FVector(0.0f, 1.0f, 0.0f));
		}
		break;
	case ETrapState::Sprung:
		if (MatDynamic)
		{
			GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Blue, (Role == ROLE_Authority) ? TEXT("Auth") : TEXT("Client"));
			MatDynamic->SetVectorParameterValue("InputColor", FVector(1.0f, 0.0f, 0.0f));
		}
		break;
	default:
		break;
	}

	if (Role < ROLE_Authority)
	{
		ServerUpdateTrapState(trapState);
	}
}

void ASTrap::OnRep_Flag()
{
	// When this is called, bFlag already contains the new value. This
	// just notifies you when it changes.
	UpdateTrapState(trapState);
}

void ASTrap::ServerUpdateTrapState_Implementation(ETrapState newState)
{
	UpdateTrapState(newState);
}

bool ASTrap::ServerUpdateTrapState_Validate(ETrapState newState)
{
	return true;
}

void ASTrap::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASTrap, trapState);
	DOREPLIFETIME(ASTrap, MatDynamic);
	DOREPLIFETIME(ASTrap, bFlag);
}
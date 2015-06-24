// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SurvivalGame.h"
#include "STrap.h"
#include "SCharacter.h"


// Sets default values
ASTrap::ASTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set all the Default values
	isActive = true;

	wasSet = false;

	trapRadius = 40.0f;

	trapState = 0.0f;

	// Collision Sphere for our player interaction.
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(trapRadius);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));

	// Create and position a mesh component so we can see where our sphere is
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Items/Meshes/Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}
	SphereVisual->SetCollisionProfileName(TEXT("Trigger"));

	//Delegate declaration.
	OnActorBeginOverlap.AddDynamic(this, &ASTrap::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASTrap::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASTrap::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* MeshComp = SphereVisual;
	if (MeshComp)
	{
		MatDynamic = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
	}
	
}

// Called every frame
void ASTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isActive)
	{
		trapState = 0.0f;
		MatDynamic->SetVectorParameterValue("InputColour", FVector(0.0f, 1.0f, 1.0f));
	}
	else if (!wasSet)
	{
		trapState = 2.0f;
		//MatDynamic->SetScalarParameterValue("InputColour", 7);
	}
	else
	{
		trapState = 1.0f;
	}
}

//Do something with the other actor.
void ASTrap::OnOverlap(AActor* OtherActor)
{
	if (isActive)
	{
		if (OtherActor && wasSet == true)
		{
			isActive = false;
		}
	}

}

void ASTrap::OnOverlapEnd(AActor* OtherActor)
{
	/*if (!wasSet)
	{
		wasSet = true;
		isActive = true;
	}
	*/

}

void ASTrap::SetTrap(AActor* OtherActor)
{
	if (!wasSet)
	{
		wasSet = true;
		isActive = true;
	}
}




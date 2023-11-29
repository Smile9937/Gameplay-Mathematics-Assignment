// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"
#include "CollisionSubsystem.h"

// Sets default values
AGround::AGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FVector BoxSize = FVector(100, 100, 100);
	BoxComponent->InitBoxExtent(BoxSize);
	BoxComponent->SetSimulatePhysics(false);

	SetRootComponent(BoxComponent);

	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("Collision"));
}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->SetSize(BoxComponent->GetScaledBoxExtent());
	
	const auto Subsystem = GetWorld()->GetSubsystem<UCollisionSubsystem>();

	Subsystem->RegisterCollider(CollisionComponent);

}

// Called every frame
void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AGround::GetSize()
{
	return BoxComponent->Bounds.BoxExtent;
}

FVector AGround::GetPosition()
{
	return GetActorLocation();
}


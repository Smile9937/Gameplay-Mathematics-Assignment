// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FVector BoxSize = FVector(100, 100, 100);

	BoxComponent->InitBoxExtent(BoxSize);
	BoxComponent->SetSimulatePhysics(false);

	SetRootComponent(BoxComponent);

	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("Collision"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(BoxComponent);
	CameraComponent->SetRelativeLocation(FVector(0, 0, 100.f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->SetSize(BoxComponent->GetScaledBoxExtent());

	Subsystem = GetWorld()->GetSubsystem<UCollisionSubsystem>();
	Subsystem->RegisterCollider(CollisionComponent);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TransformedVector = UKismetMathLibrary::TransformDirection(GetActorTransform(), MoveVector);

	TransformedVector *= MoveSpeed;
	TransformedVector.Z -= GravityScale;

	if (Jumping)
	{
		TransformedVector.Z += JumpValue;
	}

	if (Subsystem->CheckCollision(CollisionComponent))
	{
		TransformedVector = CollisionComponent->ClampToCollision(TransformedVector);
	}
	else
	{
		CollisionComponent->SetOldPosition();
	}

	SetActorLocation(GetActorLocation() + DeltaTime * TransformedVector);

}

void APlayerCharacter::Look_Implementation(const FVector2D Vector)
{
	// Rotate directly on the horizontal axis
	AddActorLocalRotation(
		FRotator(
			0.f,
			Vector.X,
			0.f)
	);

	// Clamp vertical axis
	CurrentLookRotation += Vector.Y;
	CurrentLookRotation = FMath::ClampAngle(
		CurrentLookRotation,
		-90.f,
		90.f
	);

	CameraComponent->SetWorldRotation(
		FRotator(
			CurrentLookRotation,
			GetActorRotation().Yaw,
			0.f)
	);
}

void APlayerCharacter::Move_Implementation(const FVector2D Vector)
{
	MoveVector.X = Vector.Y;
	MoveVector.Y = -Vector.X;
	MoveVector.Z = 0.f;

	MoveVector.Normalize();
}

void APlayerCharacter::Jump_Implementation(const float Value)
{
	JumpValue = JumpCurve->GetFloatValue(Value);
}

void APlayerCharacter::StartJump_Implementation()
{
	if (CollisionComponent->CollidingFromTop())
	{
		Jumping = true;
	}
}

void APlayerCharacter::StopJump_Implementation()
{
	Jumping = false;
	JumpValue = 0;
}

FVector APlayerCharacter::GetSize()
{
	return BoxComponent->Bounds.BoxExtent;
}

FVector APlayerCharacter::GetPosition()
{
	return GetActorLocation();
}



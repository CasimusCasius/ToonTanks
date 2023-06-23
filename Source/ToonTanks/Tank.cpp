// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyLogs.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerControllerRef = Cast<APlayerController>( GetController());
	
	
}
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;

	if (PlayerControllerRef && PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red);
		RotateTurret(HitResult.ImpactPoint);
	}

}
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this,&ATank::Fire);
}
void ATank::Move(float Value) 
{
	FVector DeltaLocation(0.f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaLocation.X = Value * TankSpeed* DeltaTime;
	AddActorLocalOffset(DeltaLocation,true);
	
}
void ATank::Turn(float Value) 
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value*TurnRate* UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "GAP.h"
#include "GravityCharacter.h"

#include "GravityMovementComponent.h"



DEFINE_LOG_CATEGORY_STATIC(LogCharacter, Log, All);


AGravityCharacter::AGravityCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGravityMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Initialize axis names for controls.
	MoveForwardAxisName = TEXT("MoveForward");
	MoveRightAxisName = TEXT("MoveRight");
}

void AGravityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings.
	PlayerInputComponent->BindAxis(*MoveForwardAxisName, this, &AGravityCharacter::MoveForward);
	PlayerInputComponent->BindAxis(*MoveRightAxisName, this, &AGravityCharacter::MoveRight);
}

void AGravityCharacter::ApplyDamageMomentum(float DamageTaken, const FDamageEvent& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	const UDamageType* DmgTypeCDO = DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>();
	const float ImpulseScale = DmgTypeCDO->DamageImpulse;

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (ImpulseScale > 3.0f && CharacterMovement != NULL)
	{
		FHitResult HitInfo;
		FVector ImpulseDir;
		DamageEvent.GetBestHitInfo(this, PawnInstigator, HitInfo, ImpulseDir);

		FVector Impulse = ImpulseDir * ImpulseScale;
		const bool bMassIndependentImpulse = !DmgTypeCDO->bScaleMomentumByMass;

		// Limit Z momentum added if already going up faster than jump (to avoid blowing character way up into the sky).
		{
			FVector MassScaledImpulse = Impulse;
			if (!bMassIndependentImpulse && CharacterMovement->Mass > SMALL_NUMBER)
			{
				MassScaledImpulse = MassScaledImpulse / CharacterMovement->Mass;
			}

			const FVector AxisZ = GetActorQuat().GetAxisZ();
			if ((CharacterMovement->Velocity | AxisZ) > GetDefault<UCharacterMovementComponent>(CharacterMovement->GetClass())->JumpZVelocity && (MassScaledImpulse | AxisZ) > 0.0f)
			{
				Impulse = FVector::VectorPlaneProject(Impulse, AxisZ) + AxisZ * ((Impulse | AxisZ) * 0.5f);
			}
		}

		CharacterMovement->AddImpulse(Impulse, bMassIndependentImpulse);
	}
}

FVector AGravityCharacter::GetPawnViewLocation() const
{
	return GetActorLocation() + GetActorQuat().GetAxisZ() * BaseEyeHeight;
}

void AGravityCharacter::PostNetReceiveLocationAndRotation()
{
	// Always consider Location as changed if we were spawned this tick as in that case our replicated Location was set as part of spawning, before PreNetReceive().
	if (ReplicatedMovement.Location == GetActorLocation() && ReplicatedMovement.Rotation == GetActorRotation() && CreationTime != GetWorld()->TimeSeconds)
	{
		return;
	}

	if (Role == ROLE_SimulatedProxy)
	{
		const FVector OldLocation = GetActorLocation();
		const FQuat OldRotation = GetActorQuat();
		const FQuat NewRotation = ReplicatedMovement.Rotation.Quaternion();

		// Correction to make sure pawn doesn't penetrate floor after replication rounding.
		ReplicatedMovement.Location += NewRotation.GetAxisZ() * 0.01f;

		SetActorLocationAndRotation(ReplicatedMovement.Location, ReplicatedMovement.Rotation, /*bSweep=*/ false);

		INetworkPredictionInterface* PredictionInterface = Cast<INetworkPredictionInterface>(GetMovementComponent());
		if (PredictionInterface)
		{
			PredictionInterface->SmoothCorrection(OldLocation, OldRotation, ReplicatedMovement.Location, NewRotation);
		}
	}
}

void AGravityCharacter::LaunchCharacterRotated(FVector LaunchVelocity, bool bHorizontalOverride, bool bVerticalOverride)
{
	UE_LOG(LogCharacter, Verbose, TEXT("ACharacter::LaunchCharacterRotated '%s' %s"), *GetName(), *LaunchVelocity.ToCompactString());

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (CharacterMovement)
	{
		if (!bHorizontalOverride && !bVerticalOverride)
		{
			CharacterMovement->Launch(GetVelocity() + LaunchVelocity);
		}
		else if (bHorizontalOverride && bVerticalOverride)
		{
			CharacterMovement->Launch(LaunchVelocity);
		}
		else
		{
			FVector FinalVel;
			const FVector Velocity = GetVelocity();
			const FVector AxisZ = GetActorQuat().GetAxisZ();

			if (bHorizontalOverride)
			{
				FinalVel = FVector::VectorPlaneProject(LaunchVelocity, AxisZ) + AxisZ * (Velocity | AxisZ);
			}
			else // if (bVerticalOverride)
			{
				FinalVel = FVector::VectorPlaneProject(Velocity, AxisZ) + AxisZ * (LaunchVelocity | AxisZ);
			}

			CharacterMovement->Launch(FinalVel);
		}

		OnLaunched(LaunchVelocity, bHorizontalOverride, bVerticalOverride);
	}
}

FORCEINLINE class UGravityMovementComponent* AGravityCharacter::GetGravityCharacterMovement() const
{
	return Cast<UGravityMovementComponent>(GetMovementComponent());
}

void AGravityCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// Add forward movement.
		AddMovementInput(FVector::VectorPlaneProject(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X),
			GetActorQuat().GetAxisZ()).GetSafeNormal(), Value);
	}
}

void AGravityCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FVector AxisZ = GetActorQuat().GetAxisZ();

		// Add side movement.
		AddMovementInput(AxisZ ^ FVector::VectorPlaneProject(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X),
			AxisZ).GetSafeNormal(), Value);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"

#include "VRBPDatatypes.generated.h"

USTRUCT()
struct FBPVRComponentPosRep
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FVector_NetQuantize100 Position;
	UPROPERTY()
		FRotator Orientation;
};

/*
Interactive Collision With Physics = Held items can be offset by geometry, uses physics for the offset, pushes physics simulating objects with weight taken into account
Interactive Collision With Sweep = Held items can be offset by geometry, uses sweep for the offset, pushes physics simulating objects, no weight
Sweep With Physics = Only sweeps movement, will not be offset by geomtry, still pushes physics simulating objects, no weight
Physics Only = Does not sweep at all (does not trigger OnHitEvents), still pushes physics simulating objects, no weight
*/
UENUM(Blueprintable)
enum EGripCollisionType
{
	InteractiveCollisionWithPhysics,
	InteractiveCollisionWithSweep,
	InteractiveHybridCollisionWithSweep,
	SweepWithPhysics,
	PhysicsOnly
};

USTRUCT()
struct FBPActorGripInformation
{
	GENERATED_BODY()
public:
	UPROPERTY()
		AActor * Actor;
	UPROPERTY()
		TEnumAsByte<EGripCollisionType> GripCollisionType;
	UPROPERTY()
		bool bColliding;
	UPROPERTY()
		FTransform RelativeTransform;
	UPROPERTY()
		bool bOriginalReplicatesMovement;

	// For multi grip situations
	UPROPERTY()
		USceneComponent * SecondaryAttachment;
	//UPROPERTY()
	//	FTransform SecondaryRelativeTransform;
	UPROPERTY()
		bool bHasSecondaryAttachment;
	// Allow hand to not be primary positional attachment?
	// End multi grip



	/** Physics scene index of the body we are grabbing. */
	int32 SceneIndex;
	/** Pointer to PhysX joint used by the handle*/
	physx::PxD6Joint* HandleData;
	/** Pointer to kinematic actor jointed to grabbed object */
	physx::PxRigidDynamic* KinActorData;


	FBPActorGripInformation()
	{
		HandleData = NULL;
		KinActorData = NULL;

		Actor = nullptr;
		bColliding = false;
		GripCollisionType = EGripCollisionType::InteractiveCollisionWithSweep;


		SecondaryAttachment = nullptr;
		bHasSecondaryAttachment = false;
		//bHandIsPrimaryReference = true;
	}
};
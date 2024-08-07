// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGamePlayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);


	AActor* CurrentOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector end = EyeLocation + (EyeRotation.Vector() * 1000.f);

	//FHitResult Hit;
	//bool bBlockHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, end, ObjectQueryParams);


	TArray<FHitResult> Hits;
	FCollisionShape shape;
	shape.SetSphere(30.0f);

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, end, FQuat::Identity, ObjectQueryParams, shape);

	FColor LineColor = bBlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits) {
		AActor* HitActor = Hit.GetActor();

		if (HitActor) {
			if (HitActor->Implements<USGamePlayInterface>()) {
				APawn* MPawn = Cast<APawn>(HitActor);

				ISGamePlayInterface::Execute_Interact(HitActor, MPawn);
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 32, LineColor, false, 2.0f);
	}

	

	DrawDebugLine(GetWorld(), EyeLocation, end, LineColor, false, 2.0f, 0, 2.0f);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"
#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    RootComponent = MeshComp;

    AttribueComp = CreateDefaultSubobject<USAttributeComponent>("AttribueComp");
    AttribueComp->OnHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);
}

void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0)
    {
        MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}

